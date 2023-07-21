import argparse
import copy
import os

import mmcv
import numpy as np
import torch
from mmcv import Config
from mmcv.parallel import MMDistributedDataParallel
from mmcv.runner import load_checkpoint
from torchpack import distributed as dist
from torchpack.utils.config import configs
from tqdm import tqdm

from mmdet3d.core import LiDARInstance3DBoxes
from mmdet3d.datasets import build_dataloader, build_dataset
from mmdet3d.models import build_model

########
from tools.viz_utils import PCDPublisher,ImagePublisher, CircleMarkerPublisher, Cube_Publisher

from tools.bev_output_utils import Output_Module

import time
import pickle,cv2
import rclpy
from rclpy.node import Node
rclpy.init()
########

def recursive_eval(obj, globals=None):
    if globals is None:
        globals = copy.deepcopy(obj)

    if isinstance(obj, dict):
        for key in obj:
            obj[key] = recursive_eval(obj[key], globals)
    elif isinstance(obj, list):
        for k, val in enumerate(obj):
            obj[k] = recursive_eval(val, globals)
    elif isinstance(obj, str) and obj.startswith("${") and obj.endswith("}"):
        obj = eval(obj[2:-1], globals)
        obj = recursive_eval(obj, globals)

    return obj


def main() -> None:
    loop=True

    dist.init()

    parser = argparse.ArgumentParser()
    parser.add_argument("config", metavar="FILE")
    parser.add_argument("--mode", type=str, default="gt", choices=["gt", "pred"])
    parser.add_argument("--checkpoint", type=str, default=None)
    parser.add_argument("--split", type=str, default="val", choices=["train", "val"])
    parser.add_argument("--bbox-classes", nargs="+", type=int, default=None)
    parser.add_argument("--bbox-score", type=float, default=None)
    parser.add_argument("--map-score", type=float, default=0.5)
    parser.add_argument("--out-dir", type=str, default="viz")

    args, opts = parser.parse_known_args()

    configs.load(args.config, recursive=True)

    configs.update(opts)

    cfg = Config(recursive_eval(configs), filename=args.config)

    torch.backends.cudnn.benchmark = cfg.cudnn_benchmark
    torch.cuda.set_device(dist.local_rank())

    # build the dataloader
    dataset = build_dataset(cfg.data[args.split])
    dataflow = build_dataloader(
        dataset,
        samples_per_gpu=1,
        workers_per_gpu=cfg.data.workers_per_gpu,
        dist=True,
        shuffle=False,
    )

    # build the model and load checkpoint
    if args.mode == "pred":
        model = build_model(cfg.model)
        load_checkpoint(model, args.checkpoint, map_location="cpu")

        model = MMDistributedDataParallel(
            model.cuda(),
            device_ids=[torch.cuda.current_device()],
            broadcast_buffers=False,
        )
        model.eval()


    #########
    # with open('/bevfusion/dataflow.pkl', 'rb') as f: 
    #     dataflow = pickle.load(f)
    #     dataflow = dataflow[0]


    pcd_publisher = PCDPublisher("lidar_pointcloud")
    circle_marker_publisher = CircleMarkerPublisher("circle_markers")
    cube_publisher =Cube_Publisher("bounding_box_markers")

    output_publisher = Output_Module("bev_output")
    #########
    while True:
        for data in tqdm(dataflow):
            metas = data["metas"].data[0][0]
            name = "{}-{}".format(metas["timestamp"], metas["token"])

            if args.mode == "pred":
                with torch.inference_mode():
                    outputs = model(**data)

            if args.mode == "gt" and "gt_bboxes_3d" in data:
                bboxes = data["gt_bboxes_3d"].data[0][0].tensor.numpy()
                labels = data["gt_labels_3d"].data[0][0].numpy()

                if args.bbox_classes is not None:
                    indices = np.isin(labels, args.bbox_classes)
                    bboxes = bboxes[indices]
                    labels = labels[indices]

                bboxes[..., 2] -= bboxes[..., 5] / 2
                bboxes = LiDARInstance3DBoxes(bboxes, box_dim=9)
            elif args.mode == "pred" and "boxes_3d" in outputs[0]:
                bboxes = outputs[0]["boxes_3d"].tensor.numpy()
                scores = outputs[0]["scores_3d"].numpy()
                labels = outputs[0]["labels_3d"].numpy()

                if args.bbox_classes is not None:
                    indices = np.isin(labels, args.bbox_classes)
                    bboxes = bboxes[indices]
                    scores = scores[indices]
                    labels = labels[indices]

                if args.bbox_score is not None:
                    indices = scores >= args.bbox_score
                    bboxes = bboxes[indices]
                    scores = scores[indices]
                    labels = labels[indices]

                bboxes[..., 2] -= bboxes[..., 5] / 2
                bboxes = LiDARInstance3DBoxes(bboxes, box_dim=9)
            else:
                bboxes = None
                labels = None

            if args.mode == "gt" and "gt_masks_bev" in data:
                masks = data["gt_masks_bev"].data[0].numpy()
                masks = masks.astype(np.bool)
            elif args.mode == "pred" and "masks_bev" in outputs[0]:
                masks = outputs[0]["masks_bev"].numpy()
                masks = masks >= args.map_score
            else:
                masks = None










            scores = labels







            bin_path=metas["lidar_path"]
            cube_publisher.publish_boxes(bboxes,labels,classes=cfg.object_classes)
            output_publisher.publish_boxes(bboxes,labels,scores,classes=cfg.object_classes)
            
            time.sleep(0.1)
            
            if os.path.isfile(bin_path):
                #print('File exists!')
                pcd_publisher.publish_pcd(bin_path)
            #rclpy.spin(circle_marker_publisher)   
            circle_marker_publisher.publish_circles() 
            
        if not loop: break


        
    circle_marker_publisher.destroy_node()
    rclpy.shutdown()    

if __name__ == "__main__":
    main()

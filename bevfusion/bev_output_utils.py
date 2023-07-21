import rclpy
from rclpy.node import Node
from sensor_msgs.msg import PointCloud2, PointField, Image
import numpy as np
from visualization_msgs.msg import Marker, MarkerArray
from geometry_msgs.msg import Point
from custom_msgs.msg import OutputArray, Bbox, Output

from cv_bridge import CvBridge
from matplotlib import pyplot as plt
from typing import List, Optional, Tuple
import cv2
import os
import mmcv
import copy
from mmdet3d.core import LiDARInstance3DBoxes



class Output_Module(Node):
    def __init__(self, topic_name):
        super().__init__('bev_output')
        self.cube_publisher= self.create_publisher(OutputArray, topic_name, 1)

    def publish_boxes(self,bboxes,labels, scores, classes):
        i = 0
        # marker_array = MarkerArray()
        output_array=OutputArray()
        output_array.header.frame_id = "frame"+str(i)
        output_array.header.stamp=self.get_clock().now().to_msg()
        
        

        # # Delete previously published markers
        # # delete_marker = Marker()
        # delete_marker = Output()
        # delete_bbox = Bbox()
        # delete_bbox.pos_x=0.0
        # delete_bbox.pos_y=0.0
        # delete_bbox.width=0.0
        # delete_bbox.length=0.0
        # delete_bbox.height=0.0
        # delete_bbox.yaw=0.0

        # # delete_marker.action = Marker.DELETEALL
        # delete_marker.box = delete_bbox
        # delete_marker.score = 0.0
        # delete_marker.label = 0
        # # delete_marker.ns = "bboxes"
        # marker_array.outputs.append(delete_marker)
        
        # Publish new markers
        for idx, bbox in enumerate(bboxes):
            # print(labels[idx])
            # print(classes[labels[idx]])
            if (labels[idx] == 0 or labels[idx] == 1): #only publish car/truck bboxes
                # marker = Marker()
                output=Output()
                # marker.header.frame_id = "map"
                bbox_msg=Bbox()
                bbox_msg.pos_x=float(bbox[0])
                bbox_msg.pos_y=float(bbox[1])
                bbox_msg.width=float(bbox[3])
                bbox_msg.length=float(bbox[4])
                bbox_msg.height=float(bbox[5])
                bbox_msg.yaw=-float(bbox[6])
                
                output.box=bbox_msg
                output.score=round(float(scores[idx]),4)
                output.label=int(labels[idx])
                # print(type(labels[idx]))
                
                # if labels[idx] == 0:
                #     marker.color.r = 0.0
                #     marker.color.g = 0.0
                #     marker.color.b = 1.0
                # if labels[idx] == 1:
                #     marker.color.r = 1.0
                #     marker.color.g = 0.0
                #     marker.color.b = 0.0
                # marker.color.a = 1.0
                # marker.lifetime.sec = 10  # 10 seconds in nanoseconds
                output_array.outputs.append(output)
                i += 1

        self.cube_publisher.publish(output_array)

OBJECT_PALETTE = {
    "car": (255, 158, 0),
    "truck": (255, 99, 71),
    "construction_vehicle": (233, 150, 70),
    "bus": (255, 69, 0),
    "trailer": (255, 140, 0),
    "barrier": (112, 128, 144),
    "motorcycle": (255, 61, 99),
    "bicycle": (220, 20, 60),
    "pedestrian": (0, 0, 230),
    "traffic_cone": (47, 79, 79),
}


def visualize_camera(
    fpath: str,
    image: np.ndarray,
    *,
    bboxes: Optional[LiDARInstance3DBoxes] = None,
    labels: Optional[np.ndarray] = None,
    transform: Optional[np.ndarray] = None,
    classes: Optional[List[str]] = None,
    color: Optional[Tuple[int, int, int]] = None,
    thickness: float = 4,
) -> None:
    canvas = image.copy()
    canvas = cv2.cvtColor(canvas, cv2.COLOR_RGB2BGR)

    if bboxes is not None and len(bboxes) > 0:
        corners = bboxes.corners
        num_bboxes = corners.shape[0]

        coords = np.concatenate(
            [corners.reshape(-1, 3), np.ones((num_bboxes * 8, 1))], axis=-1
        )
        transform = copy.deepcopy(transform).reshape(4, 4)
        coords = coords @ transform.T
        coords = coords.reshape(-1, 8, 4)

        indices = np.all(coords[..., 2] > 0, axis=1)
        coords = coords[indices]
        labels = labels[indices]

        indices = np.argsort(-np.min(coords[..., 2], axis=1))
        coords = coords[indices]
        labels = labels[indices]

        coords = coords.reshape(-1, 4)
        coords[:, 2] = np.clip(coords[:, 2], a_min=1e-5, a_max=1e5)
        coords[:, 0] /= coords[:, 2]
        coords[:, 1] /= coords[:, 2]

        coords = coords[..., :2].reshape(-1, 8, 2)
        for index in range(coords.shape[0]):
            name = classes[labels[index]]
            for start, end in [
                (0, 1),
                (0, 3),
                (0, 4),
                (1, 2),
                (1, 5),
                (3, 2),
                (3, 7),
                (4, 5),
                (4, 7),
                (2, 6),
                (5, 6),
                (6, 7),
            ]:
                cv2.line(
                    canvas,
                    coords[index, start].astype(np.int),
                    coords[index, end].astype(np.int),
                    color or OBJECT_PALETTE[name],
                    thickness,
                    cv2.LINE_AA,
                )
        canvas = canvas.astype(np.uint8)
    canvas = cv2.cvtColor(canvas, cv2.COLOR_BGR2RGB)

    mmcv.mkdir_or_exist(os.path.dirname(fpath))
    mmcv.imwrite(canvas, fpath)

def visualize_lidar(
    fpath: str,
    lidar: Optional[np.ndarray] = None,
    *,
    bboxes: Optional[LiDARInstance3DBoxes] = None,
    labels: Optional[np.ndarray] = None,
    classes: Optional[List[str]] = None,
    xlim: Tuple[float, float] = (-50, 50),
    ylim: Tuple[float, float] = (-50, 50),
    color: Optional[Tuple[int, int, int]] = None,
    radius: float = 15,
    thickness: float = 25,
) -> None:
    
    fig = plt.figure(figsize=(xlim[1] - xlim[0], ylim[1] - ylim[0]))

    ax = plt.gca()
    ax.set_xlim(*xlim)
    ax.set_ylim(*ylim)
    ax.set_aspect(1)
    ax.set_axis_off()

    if lidar is not None:
        plt.scatter(
            lidar[:, 0],
            lidar[:, 1],
            s=radius,
            c="white",
        )

    if bboxes is not None and len(bboxes) > 0:
        coords = bboxes.corners[:, [0, 3, 7, 4, 0], :2]
        for index in range(coords.shape[0]):
            name = classes[labels[index]]
            plt.plot(
                coords[index, :, 0],
                coords[index, :, 1],
                linewidth=thickness,
                color=np.array(color or OBJECT_PALETTE[name]) / 255,
            )

    mmcv.mkdir_or_exist(os.path.dirname(fpath))
    fig.savefig(
        fpath,
        dpi=10,
        facecolor="black",
        format="png",
        bbox_inches="tight",
        pad_inches=0,
    )
    plt.close()

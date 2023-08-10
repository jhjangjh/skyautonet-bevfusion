# skyautonet bevfusion post-processing
2023 Summer Internship Program at **SkyAutoNet**

This is a post-processing repository of BEVfusion project.
> https://github.com/mit-han-lab/bevfusion

## Tracking
<img src="assets/tracking.gif" width="40%"/>

### Prerequisites
- OpenCV >= 4.2.0
- ROS2(Foxy)

### Algorithm
Use SORT(Simple Online Realtime Tracking) Algorithm with Bird-Eye View bounding boxes.

- Kalman Filter
- Hungraian Algorithm

### Usage
```linux
ros2 launch tracking_algorithm tracking_launch.py
```

### Citation
> https://github.com/abewley/sort **abewley/sort**
> 
> https://github.com/mcximing/sort-cpp **mcximing/sort-cpp**
>
> https://github.com/Hyun-je/SORT-ros **Hyun-je/SORT-ros**

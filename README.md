# srpb_move_base

This package is closely related to the **main** package of the [SRPB](https://github.com/rayvburn/srpb) - a benchmark for the quantitative evaluation of social robot navigation.

`srpb_move_base` package allows logging data while the robot is navigating (using ROS1 navigation stack).
The `move_base` package was extracted from the original [`ros-planning/navigation`](https://github.com/ros-planning/navigation) metapackage with a whole history preserved. Reference branches will be updated to upstream changes and `<reference branch>-benchmark` branches will be rebased.

Currently, only the version for ROS `melodic` is supported.

## Usage

1. In your typical setup, switch from the classical `move_base` node to `srpb_move_base` node from the `srpb_move_base` package. This node has all functionalities of the classical `move_base`, plus some extensions to provide logging of the robot's and its environment state.
Additional parameters are:
    * `log_filename` - path to the file with the data logged during the robot's run to the goal pose; note that any directory in which the output file is placed must be created beforehand; also note that the path will contain only the basename of the log file, as it will contain the date too.
    * `log_frame_id` - the name of the coordinate frame that logged data will be transformed into; `map` is recommended when recordings are meant to be visualized later.
2. Run your navigation just as usual.

TBD...

## Acknowledgments

The foundations of this package are:
* [ROS1 navigation stack](https://github.com/ros-planning/navigation) metapackage. The `move_base` package was extracted from the metapackage as stated in the [Upstream updates](#Upstream updates) section.
* [`MRPB`: Mobile Robot Local Planning Benchmark](https://github.com/NKU-MobFly-Robotics/local-planning-benchmark). There might be some shared sections of code, but overall, the original package has undergone a major overhaul.

## Upstream updates

Upstream updates to [`ros-planning/navigation`](https://github.com/ros-planning/navigation) (note that `NKU-MobFly-Robotics/local-planning-benchmark` does not seem to be supported anymore) must be handled by hand. The procedure is as follows (based on [stackoverflow:47084338](https://stackoverflow.com/a/47084338)):

```bash
git clone <REPO>
cd <REPO>
for i in $(git branch -r | sed "s/.*origin\///"); do git branch -t $i origin/$i; done
git filter-branch --prune-empty --subdirectory-filter move_base -- --all
git remote remove origin
git remote add origin git@github.com:rayvburn/srpb_move_base.git
git push origin '*:*'
git push origin --all
git push origin --tags
```

Last upstream update 2022.07.11.

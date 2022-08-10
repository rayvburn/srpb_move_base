# move_base_benchmark

Package developed on top of:

* [ROS1 navigation stack](https://github.com/ros-planning/navigation) metapackage
* [`MRPB`: Mobile Robot Local Planning Benchmark](https://github.com/NKU-MobFly-Robotics/local-planning-benchmark).

`move_base` package was extracted from the [`ros-planning/navigation`](https://github.com/ros-planning/navigation) metapackage with a whole history preserved. Reference branches will be updated to upstream changes and `<reference branch>-benchmark` branches will be rebased onto.

Currently only `melodic` version is supported.

## Local planning benchmark

To use all features of the benchmark, one may have a look at parameters and possible remappings. For example, these may be included into `launch` file:

```xml
<param name="log_filename" value="path/to/log/file"/>
<remap from="cmd_vel" to="custom/cmd/vel/topic"/>
<remap from="odom" to="custom/odom/topic"/>
```

## Upstream updates

Upstream updates to [`ros-planning/navigation`](https://github.com/ros-planning/navigation) (note that `NKU-MobFly-Robotics/local-planning-benchmark` does not seem to be maintained anymore) must be handled by hand. Procedure is as follows (based on [stackoverflow:47084338](https://stackoverflow.com/a/47084338)):

```bash
git clone <REPO>
cd <REPO>
for i in $(git branch -r | sed "s/.*origin\///"); do git branch -t $i origin/$i; done
git filter-branch --prune-empty --subdirectory-filter move_base -- --all
git remote remove origin
git remote add origin git@github.com:rayvburn/move_base_benchmark.git
git push origin '*:*'
git push origin --all
git push origin --tags
```

Last upstream update 2022.07.11.

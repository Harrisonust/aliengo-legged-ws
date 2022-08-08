The unitree_legged_sdk is mainly used for communication between PC and Controller board.
It also can be used on other PCs with UDP.

## Dependencies
* [Boost](http://www.boost.org) (version 1.5.4 or higher)
* [CMake](http://www.cmake.org) (version 2.8.3 or higher)
* [LCM](https://lcm-proj.github.io) (version 1.4.0 or higher)
    build LCM:
    ```sh
    cd lcm-x.x.x
    mkdir build
    cd build
    cmake ../
    make
    sudo make install
    ```

## Build Legged Workspace
```sh
mkdir build
cd build
cmake ../
make
```

## Run
Run the controlling with:
```sh
sudo ./aliengo-legged-ws/build/optimal_nav
```
This program runs in a forever loop and will keep listening the planned position and producing optimal motions.

Other testing programs can also be found under `example/`.
:warning: Run all examples with **'sudo'** to prevent memory locking.
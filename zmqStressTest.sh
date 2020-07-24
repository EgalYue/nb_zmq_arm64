#!/bin/bash

echo "============Start=================="
echo "==== Close app first ==="
cd /home/yuehu/Downloads
adb -s B2D120D12F0092 uninstall com.segway.robot.algo.loomogo_nav_app
sleep 2s


echo "--------------------Disconnect 30 s----------------------------------"
echo ">>> Installing app"
adb -s B2D120D12F0092 install loomogo_nav_app-debug.apk
adb -s B2D120D12F0092 shell am start -n com.segway.robot.algo.loomogo_nav_app/com.segway.robot.application.AlgoActivity
sleep 1m # run 
echo ">>> Uninstalling app"
adb -s B2D120D12F0092 uninstall com.segway.robot.algo.loomogo_nav_app
echo ">>> Sleeping..."
sleep 30s # disconnect
echo "-------------------------------------------------------------------\n"


i=1
while [ $i -le 65 ]
do
    echo "--------------------Disconnect $i min----------------------------------"
    echo ">>> Installing app"
    adb -s B2D120D12F0092 install loomogo_nav_app-debug.apk
    adb -s B2D120D12F0092 shell am start -n com.segway.robot.algo.loomogo_nav_app/com.segway.robot.application.AlgoActivity
    sleep 1m # run 
    echo ">>> Uninstalling app"
    adb -s B2D120D12F0092 uninstall com.segway.robot.algo.loomogo_nav_app
    echo ">>> Sleeping..."
    sleep "$i"m # disconnect
    echo "-------------------------------------------------------------------\n"

    let i=i*2
done

echo ">>> Installing app"
adb -s B2D120D12F0092 install loomogo_nav_app-debug.apk
adb -s B2D120D12F0092 shell am start -n com.segway.robot.algo.loomogo_nav_app/com.segway.robot.application.AlgoActivity

echo "============End=================="
#============ end ========================
#!/bin/bash

date "+%Y-%m-%d %H:%M:%S" | xargs -I {} echo {}
./usbDrDAQRead
date "+%Y-%m-%d %H:%M:%S" | xargs -I {} echo {}
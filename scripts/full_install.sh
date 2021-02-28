#!/usr/bin/env bash

dir=$PWD

cd install
./tune_ports.sh

# *** Create links ***
./create_links.sh
cd $dir

# *** Clone and build Urho3D ***
cd install/Urho3D
./assembly.sh full all
cd $dir

# *** Build TacticsVictory ***
cd Linux
./assembly.sh full all
cd $dir

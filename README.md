# Wastewater System Model and Simulation
[DEVS](https://en.wikipedia.org/wiki/DEVS) model and simulation of single and combined attacks on an industrial wastewater system.

## Motivation

## Usage
To execute the simulation, run
```
source build_sim.sh
./bin/campus-evacuation | grep "id=1,"
```

Your output should look similar to this
```
time,model_id,model_name,port_name,data
0,30,P3,exit,Vehicle{src=P3,id=1,dest=}
0,21,P3 & Raven Rd,out2,Vehicle{src=P3,id=1,dest=P3 & Raven Rd to Bronson Ave & Raven Rd}
9,8,P3 & Raven Rd to Bronson Ave & Raven Rd,exit,Vehicle{src=P3,id=1,dest=P3 & Raven Rd to Bronson Ave & Raven Rd}
```

To reference the simulation options, run 
```
./bin/campus-evacuation --help
```

To execute all scenarios as a batch, run
```
source run_scenarios.sh
```

## Install
Instructions for installing this project's dependencies.

### Cadmium
Install Cadmium by running a [bootstrap script](https://github.com/braedenkloke/scripts-devssim),
or by following the instructions in the [Cadmium Installation Manual](https://devssim.carleton.ca/manuals/installation/).

Next, move this project folder to your Cadmium projects folder as such
```
cadmium-projects
|--cadmium_v2
|--model-campus-evacuation
```

Lastly, ensure you have your `CADMIUM` environment variable is set to your `cadmium_v2/include` directory
```
printenv | grep CADMIUM
```

## Further Reading
- [Cadmium and the DEVSsim Server](https://devssim.carleton.ca/): Two tools for discrete-event modeling and simulation.
- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
- [hackergrrl/art-of-readme](https://github.com/hackergrrl/art-of-readme)

## License
[MIT](https://choosealicense.com/licenses/mit/)

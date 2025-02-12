### Structure of the Agent_simulation_library project:

- **external** - Contains all external libraries necessary for running the CASE tool.
- **frontend/CASE_tool** - CASE tool used for creating simulation models in the Agent simulation library (runnable CASE_tool.cpp).
- **frontend/CASE_tool/resources** - Resources for code generation.
- **library** - The developed Agent simulation library supporting reactive agents and reasoning via Petri Nets.
- **logs** - Logs generated after simulation runs.
- **projects** - Simulation models in JSON format, loaded by the CASE tool.
- **projects/reactive/[simulation model name]/raw** - Generated data of simulation models using reactive agents designed by the CASE tool (without code addition).
- **projects/reactive/[simulation model name]/modified** - Generated data of simulation models using reactive agents designed by the CASE tool (with code addition).
- **projects/petri_net/[simulation model name]/raw** - Generated data of simulation models using agent reasoning by Petri Net designed by the CASE tool (without code addition).
- **projects/petri_net/[simulation model name]/modified** - Generated data of simulation models using agent reasoning by Petri Net designed by the CASE tool (with code addition).
- **simulation_models** - Simulation models created without the CASE tool (for function comparison).
- **units** - General classes used both in the CASE tool and the library.

### Executable files:

- **Flocking_mode_reactive_stupid** - Flocking model where the birds are represented as empty boxes with only the ability to get/set their position. The movement mechanism is managed by the agent manager.
- **Flocking_mode_reactive_intelligent** - Flocking model where the birds are represented as agents responsible for their movement and cooperation with other birds. The movement mechanism is handled within the bird agent.
- **Shop_reactive** - Shop simulation using reactive agents.
- **Shop_petri_net** - Shop simulation using Petri nets.
- **CASE_tool** - CASE tool for creating models used by the Agent simulation library.
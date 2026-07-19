#include "util/sparse_set.h"
/*
Initalise and store window info.
Intialise rendering pipeline and OpenGL state
Create World Registery
    - RegisteredWorld[MAX/N_WORLDS]  {ID, *Location}
3. Load World Data
4. Create Entity Registery
    - RegisteredEntity {ID, *Location(, type or other flags?)}
5. Build Entities and Populate Entity Registry
6. Setup Rendering Pipeline.
7. Start Physics/World Engine

Spare Set
EntityRegistery[MAX_ENTITIES]
COMP1_INDEX[MAX_ENTITIES]
COMP2_INDEX[MAX_ENTITIES]
COMP1_DATA[Dynamic]
COMP2_DATA[Dynamic]

add COMP2 to entity 5

get tail of COMP2, lets say 10
COMP2_INDEX[5] = 10
COMP2_DATA[10] = Data

- Mesh
  - *verticies
  - *indcies
  - VAO
- Material
  - *texture/s
  - shader_id
  - colour

both Mesh and Material will go in a registery so we can reuse them.

Entity
- Mesh Component
  - mesh_id
- material Component
  - material_id
Transform Component
- pos_x, pos_y, pos_z
- scale_x, scale_y, scale_z
- rotation_yaw, rotation_pitch, rotation_roll
*/


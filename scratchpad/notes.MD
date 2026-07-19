# Notes

### Physics
Time splting, find when the collision occoured. binary search
spatial partitioning, based on max speed. Hierachical bounding volumes. PLane sweep

### Style
I am likely going to rewrite most the stuff ive done from the tutorial once i finish part one, my code now is messy.
I need to get better at naming stuff.

Try stay consistent with the naming tabbing and documentation ive done in sparse_set. it takes time but it has been much easier to debug

### Archicecture
OpenGL using ID lookups for a lot of its functions. I can use a similar architecture for ECS.
Assign each entity an ID, then use that ID to "subscribe" that Entity to behavours. Eg, 
entity ID = 223
behavourIsColidable = {223}
then in physics simulations we can itterate though just the colidable list and calculate fromt here.
have a list of EntityEntry structs containing ID and and the entitys pointer. loop though that list to access to the entity?

A Mesh effectivly is a VAO + VBO + EBO. PLus index count and draw mode
A Material is a shaderProgram + textures.
A Object/Pawn is a Mesh/s with a Material/s and a position and transform

I want ot split physics and render updates, prefferablily on 2 threads, not sure how much extra scope that is. low priority.

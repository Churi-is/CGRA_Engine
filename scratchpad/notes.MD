# Notes

### Style
I am likely going to rewrite most the stuff ive done from the tutorial once i finish part one, my code now is messy.
I need to get better at naming stuff.

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

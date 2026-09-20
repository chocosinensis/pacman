```md
Ghosts:
- Blinky : red
- Pinky : pink
- Inky : sky
- Clyde : orange

States:
- Scatter
- Chase
- Frightened
- Eaten

Each level: scatter - chase - 4 times before settling in chase mode

          scatter -  chase - scatter -  chase - scatter    - chase - scatter  - chase
Lvl 1   :      7s      20s        7s      20s        5s        20s        5s      inf
Lvl 2-4 :      7s      20s        7s      20s        5s  17m13s14f        1f      inf
Lvl 5+  :      5s      20s        5s      20s        5s  17m17s14f        1f      inf

Blinky full-on chase mode when n dots remaining:
LEVEL :      1      2    3-5    6-8   9-11  12-14  15-18   19+
n     :     20     30     40     50     60     80    100   120

- No turning backwards for ghosts while traversing normally
- Next direction : the direction that will minimize distance to the **target**
- If same distance, priority : up, left, down, right

TURN AROUND 180 DEGREES ONLY WHEN:
- pacman eats a blorb (power pellet)
- going from chase to scatter
- going from scatter to chase

**Target**:

Scatter:
Blinky : (GRID_WIDTH - 2, -1)
Pinky  : (2, -1)
Inky   : (GRID_WIDTH - 1, GRID_HEIGHT - 2)
Clyde  : (1, GRID_HEIGHT - 2)

Frightened: when pacman eats blorb on lvls 1-16 and 18
GHOSTS TURN AROUND 180 DEGREES
Next direction : whatever rng says

Eaten: when pacman eats ghost
target for all : right above the gate (13, 14)
move down into the house and revert to scatter/chase

Chase:

Blinky :
Pacman's tile

Pinky :
Four tiles in front of pacman
Four tiles above and to the left if pacman is facing upwards

Inky :
Intermediate tile :
Two tiles in front of pacman
Two tiles above and to the left if pacman is facing upwards

Then, vector between int-tile and blinky's position flipped 180 degrees
That tile is inky's target

Clyde :
Pacman's tile if distance >= 8 tiles
Scatter target otherwise

```

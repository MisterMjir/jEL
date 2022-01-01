#define JEL_REGISTER_COMPONENTS
#include "jel.h"
#include <stdio.h>

struct Position {
  int x;
  int y;
};
struct Physics {
  int x_vel;
  int y_vel;
};

JEL_COMPONENT(Position, x, y);
JEL_COMPONENT(Physics, x_vel, y_vel);

int main(void)
{
  JEL_init();

  JEL_REGISTER(Position);
  JEL_REGISTER(Physics);

  JEL_Entity e = JEL_entity_create(); 

  JEL_ENTITY_SET(e, Position, 5, 5); 
  JEL_ENTITY_SET(e, Physics, 5, 5); 

  struct JEL_Query q;
  JEL_QUERY(q, Position, Physics);
  for (unsigned int t = 0; t < q.count; ++t) {
    struct PositionIt pos; JEL_IT(pos, q.tables[t], Position);
    struct PhysicsIt phys; JEL_IT(phys, q.tables[t], Physics);
    for (unsigned int i = 1; i < q.tables[t]->count; ++i) {
      //printf("Xs: %d, %d\n", pos.x[i], phys.x_vel[i]);
      pos.x[i] += phys.x_vel[i];
      pos.y[i] += phys.y_vel[i];
    }
  }
  JEL_query_destroy(&q);

  struct Position p;
  JEL_ENTITY_SET_PROP(e, Position, y, 15);
  JEL_ENTITY_GET(e, Position, &p);
  printf("Position's values: %d, %d\n", p.x, p.y);
  struct Physics ph;
  JEL_ENTITY_GET(e, Physics, &ph);
  printf("Physics's values: %d, %d\n", ph.x_vel, ph.y_vel);

  JEL_quit();

  return 0;
}

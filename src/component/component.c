#include "component.h"
#include "logger/logger.h"

/*
 * JEL_component_create
 *
 * @desc
 *   Creates a component from the given data
 *   This also safely sets components because
 *   it does a deep copy instead of a shallow
 *   copy
 * @param component
 *   Component to create
 * @param props
 *   The number of properties/members
 * @param sizes
 *   Size of each member
 * @param offsets
 *   Offset of each member
 */
void JEL_component_create(struct JEL_Component *component, unsigned int props, size_t *sizes, size_t *offsets)
{
  if (props > JEL_MAX_PROPS) {
    props = JEL_MAX_PROPS;
    JEL_log("Too many component props supplied. Given %u but max is %u. Only using the max amount.", props, JEL_MAX_PROPS);
  }

  component->props = props;
  for (unsigned int i = 0; i < props; ++i) {
    component->sizes[i] = sizes[i];
    component->offsets[i] = offsets[i];
  }
}

/*
 * JEL_component_size
 *
 * @desc
 *   Size of all of the component's
 *   members
 * @param component
 *   Component to check the size of
 * @return
 *   Sum of member sizes
 */
size_t JEL_component_size(struct JEL_Component *component)
{
  size_t size = 0;
  for (unsigned int i = 0; i < component->props; ++i) {
    size += component->sizes[i];
  }

  return size;
}

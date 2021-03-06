#include <vector>
#include <memory>

namespace ares
{

struct Component;
struct Core;
struct Transform;

struct Entity
{
  friend struct ::ares::Core;

  // Template functions

  template <typename T>
  std::shared_ptr<T> addComponent()
  {
    std::shared_ptr<T> rtn = std::make_shared<T>();
    rtn->entity = self;

    components.push_back(rtn);

    rtn->onInitialize();

    return rtn;
  }

  template <typename T> 
  std::shared_ptr<T> getComponent()
  {
      for (size_t i = 0; i < components.size(); i++)
      {
          std::shared_ptr<T> rtn = std::dynamic_pointer_cast<T>(components.at(i)); // Trying to convert every other component to the requested one

          if (!rtn) continue; // If rtn equals NULL - then continue iteration

          return rtn; // Once found it - return it
      }

      throw std::exception ("Error: couldn't find the rquested type");
  }

  void tick();
  void render();

  std::shared_ptr<Core> getCore();
  std::shared_ptr<Transform> getTransform();

private:
  std::vector<std::shared_ptr<Component>> components;
  std::weak_ptr<Core> core;
  std::weak_ptr<Entity> self;

};

}

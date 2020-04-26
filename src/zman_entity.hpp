#ifndef ZMAN_TEMPORAL_OBJECT_HPP
#define ZMAN_TEMPORAL_OBJECT_HPP

#include <memory>

namespace zman {

template<class NAMESPACE, class ID>
class entity
{
public:
    using namespace_type = NAMESPACE;
    using id_type        = ID;
    using ptr_type       = std::shared_ptr<entity>;
    using weak_ptr_type  = std::weak_ptr<entity>;

    entity(
          const namespace_type& namespac
        , const id_type&        id
    )
    : namespace_(namespac)
    , id_(id)
    {
    }

    virtual ~entity() {} 

    const namespace_type& entity_namespace() const { return namespace_; }
    const id_type& id() const { return id_; }

private:
    namespace_type namespace_;
    id_type        id_;
}; 

}

#endif

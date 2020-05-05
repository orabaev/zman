#ifndef ZMAN_ENTITY_HPP
#define ZMAN_ENTITY_HPP

#include <memory>

namespace zman {

template<class NAMESPACE, class ID, class TIMEPOINT>
class entity
{
public:
    using namespace_type = NAMESPACE;
    using id_type        = ID;
    using timepoint_type = TIMEPOINT;
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
    virtual ptr_type snap(const timepoint_type& timepoint) const { return nullptr; }

private:
    namespace_type namespace_;
    id_type        id_;
}; 

}

#endif

#ifndef SEPARATOR_H_
#define SEPARATOR_H_

#include "Component.hpp"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

class Separator : public Component
{
public:
	Separator();
	virtual ~Separator();

	virtual void tick(const float32 delta) override;
    
private:
	void initialize();
};

}
}
}

#endif /* SEPARATOR_H_ */

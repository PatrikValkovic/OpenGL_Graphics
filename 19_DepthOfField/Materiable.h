#ifndef __MATERIABLE_H__
#define __MATERIABLE_H__
#include "Material.h"

class Materiable
{
protected:
	Material _material;
public:
	Materiable(const Material& material);
	Materiable(const Materiable&) = default;
	Materiable(Materiable&&) = default;
	Materiable& operator=(const Materiable&) = default;
	Materiable& operator=(Materiable&&) = default;
	virtual ~Materiable() = default;



	inline Materiable& setMaterial(const Material& m) noexcept {
		_material = m;
		return *this;
	}	
	inline Materiable& setMaterial(Material &&m) noexcept {
		_material = std::move(m);
		return *this;
	}
	inline const Material& getMaterial() const noexcept {
		return _material;
	}
	inline Material& getMaterial() noexcept {
		return _material;
	}
};

#endif
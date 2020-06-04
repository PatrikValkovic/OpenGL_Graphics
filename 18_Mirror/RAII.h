#ifndef __RAII_H_
#define __RAII_H_

#include <type_traits>
#include<functional>
#include<glad/glad.h>

template<typename T>
class RAII
{
	static_assert(std::is_scalar<T>::value, "RAII can handle only scalars");
private:
	T _resource;
	std::function<void(T)> _destroy;
public:
	RAII() noexcept : _resource(0), _destroy(nullptr)
	{}

	RAII(std::function<void(T)> destroy, T resource) noexcept : _resource(resource), _destroy(destroy)
	{}

	template<typename FUNC, typename ...PARAMS>
	RAII(std::function<void(T)> destroy, FUNC create, PARAMS&& ...params)
		: _resource(create(std::forward<PARAMS>(params)...)), _destroy(destroy)
	{}

	RAII(const RAII&) = delete;
	RAII(RAII&&) = default;
	RAII& operator=(const RAII&) = delete;
	RAII& operator=(RAII&&) = default;

	~RAII() {
		if (_destroy) {
			_destroy(_resource);
			_destroy = nullptr;
			_resource = 0;
		}
	}

	inline const T& getResource() const noexcept {
		return _resource;
	}

	inline operator const T() const noexcept {
		return _resource;
	}

	inline T& getResource() noexcept {
		return _resource;
	}

	inline operator T() noexcept {
		return _resource;
	}

	inline void free() {
		this->~RAII();
	}

	inline operator bool() const noexcept {
		return _destroy != nullptr;
	}

	inline T operator->() noexcept {
		static_assert(std::is_pointer<T>::value, "Can't call operator -> on non-pointer type");
		return _resource;
	}

};



template<>
class RAII<void> 
{
private:
	std::function<void()> _destroy;
public:
	RAII() noexcept = default;

	RAII(std::function<void()> destroy) noexcept : _destroy(destroy)
	{}

	template<typename FUNC, typename ...PARAMS>
	RAII(std::function<void()> destroy, FUNC create, PARAMS&& ...params): RAII(destroy) {
		create(std::forward<PARAMS>(params)...);
	}

	RAII(const RAII&) = delete;
	RAII(RAII&&) = default;
	RAII& operator=(const RAII&) = delete;
	RAII& operator=(RAII&&) = default;

	~RAII() {
		if (_destroy) {
			_destroy();
			_destroy = nullptr;
		}
	}

	inline void free() {
		this->~RAII();
	}

	inline operator bool() const noexcept {
		return _destroy != nullptr;
	}
};

template<typename T=GLuint>
class RAIIArray {
	RAII<T> _raii;
public:
	RAIIArray() noexcept = default;

	RAIIArray(std::function<void(GLsizei, T const *)> destroy, T resource) noexcept
		: _raii([destroy](T r) {destroy(1, &r); }, resource)
	{}

	RAIIArray(std::function<void(GLsizei, T const *)> destroy, std::function<void(GLsizei, T*)> create)
		: RAIIArray(destroy, T(0))
	{
		create(1, &(_raii.getResource()));
	}
	~RAIIArray() = default;

	RAIIArray(const RAIIArray&) = delete;
	RAIIArray(RAIIArray&&) = default;
	RAIIArray& operator=(const RAIIArray&) = delete;
	RAIIArray& operator=(RAIIArray&&) = default;

	inline const T& getResource() const noexcept {
		return _raii;
	}

	inline operator const T() const noexcept {
		return _raii;
	}

	inline T& getResource() noexcept {
		return _raii;
	}

	inline operator T() noexcept {
		return _raii;
	}

	inline void free() {
		this->~RAIIArray();
	}

	inline operator bool() const noexcept {
		return (bool)_raii;
	}
};


#endif



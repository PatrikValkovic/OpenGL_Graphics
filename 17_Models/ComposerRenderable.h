#ifndef __COMPOSE_RENDERABLE_H__
#define __COMPOSER_RENDERABLE_H__
#include <vector>
#include <memory>
#include "Renderable.h"

class ComposerRenderable : public Renderable
{
protected:
	std::vector<std::unique_ptr<Renderable>> _renderables;
public:
	ComposerRenderable() = default;
	ComposerRenderable(std::vector<std::unique_ptr<Renderable>>&& renderables);
	ComposerRenderable(const ComposerRenderable&) = default;
	ComposerRenderable(ComposerRenderable&&) = default;
	ComposerRenderable& operator=(const ComposerRenderable&) = default;
	ComposerRenderable& operator=(ComposerRenderable&&) = default;
	virtual ~ComposerRenderable() = default;

	ComposerRenderable& addRenderable(std::unique_ptr<Renderable>&& renderable);
};

#endif
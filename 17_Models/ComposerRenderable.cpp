#include "ComposerRenderable.h"

ComposerRenderable::ComposerRenderable(std::vector<std::unique_ptr<Renderable>>&& renderables)
	: _renderables(std::move(renderables))
{}

ComposerRenderable& ComposerRenderable::addRenderable(std::unique_ptr<Renderable> && renderable)
{
	_renderables.push_back(std::move(renderable));
	return *this;
}

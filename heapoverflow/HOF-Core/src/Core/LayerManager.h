/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#pragma once
#include "Layer.h"
#include <vector>
#include <memory>
#include <queue>

namespace hof
{
	class Application;

	class LayerManager
	{
	public:
		LayerManager() = default;
		~LayerManager();

		void PushLayer(std::shared_ptr<Layer> layer);
		void PushOverlay(std::shared_ptr<Layer> overlay);
		void PopLayer(std::shared_ptr<Layer> layer);
		void PopOverlay(std::shared_ptr<Layer> overlay);
		
		

		std::vector<std::shared_ptr<Layer>>& GetLayers() { return m_Layers; }
		std::vector<std::shared_ptr<Layer>>& GetOverLays() { return m_Overlays; }
	private:
		friend Application;
		void ClearDeleteQueue();
		void PopLayerDirect(std::shared_ptr<Layer> layer);
		void PopOverlayDirect(std::shared_ptr<Layer> overlay);
	private:
		std::vector<std::shared_ptr<Layer>> m_Layers;
		std::vector<std::shared_ptr<Layer>> m_Overlays;

		
		std::queue< std::shared_ptr<Layer>> m_LayerDeleteQueue;
		std::queue< std::shared_ptr<Layer>> m_OverlayDeleteQueue;
	};
}

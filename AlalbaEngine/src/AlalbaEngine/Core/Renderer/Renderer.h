#pragma once

namespace Alalba
{
	class Renderer
	{
	public:
		Renderer() {};
		~Renderer() {};

	//	void Shutdown();
	//	void Resize();
	//	
	//	const vk::RenderPass& GetRenderPass()const { return *m_renderPass; }
	//	
	//	void PrepareCommandBuffers();
	//	void UpdateCommandBuffer(uint32_t currentFrame);

	//	void Update(Scene& scene);
	//	void DrawFrame(Scene& scene);

	//private:
	//	
	//	struct GlobalUBO {
	//		// cam
	//		glm::mat4 view;
	//		glm::mat4 proj;
	//		
	//		// light
	//		glm::mat4 lightview;
	//		glm::mat4 lightproj;
	//		// cam
	//		glm::vec4 camPos;
	//		// light
	//		glm::vec4 lightposition;
	//		glm::vec4 lightcolor;
	//	};

	//private:
	//	Scene& m_scene;
	//	// 
	//	std::unique_ptr<vk::Allocator> m_allocator;

	//	// pipeline 
	//	std::unique_ptr<vk::PipelineCache> m_pipelineCache;
	//	

	//	// shader related Global 
	//	std::unique_ptr<vk::DescriptorPool> m_globalDescPool;
	//	std::vector<std::unique_ptr<vk::DescriptorSet>> m_GlobalDescriptorSets{ vk::SwapChain::MAX_FRAMES_IN_FLIGHT };
	//	std::vector< std::unique_ptr<vk::Buffer> > m_globalUniformbuffers{ vk::SwapChain::MAX_FRAMES_IN_FLIGHT };

	//	// swapchain and renderpass 
	//	std::unique_ptr<vk::SwapChain> m_swapChain;
	//	std::unique_ptr<vk::RenderPass> m_renderPass;
	//	std::vector<std::unique_ptr<vk::FrameBuffer>> m_frameBuffers{ vk::SwapChain::MAX_FRAMES_IN_FLIGHT };
	//	
	//	std::vector<std::unique_ptr<vk::Image>> m_depthImages{ vk::SwapChain::MAX_FRAMES_IN_FLIGHT };
	//	std::vector < std::unique_ptr<vk::ImageView>> m_depthImageViews{ vk::SwapChain::MAX_FRAMES_IN_FLIGHT };
	//	
	//	// command
	//	std::unique_ptr<vk::CommandPool> m_commandPool;
	//	std::unique_ptr<vk::CommandBuffers> m_commandBuffers;

	//	// syschronize
	//	std::vector< std::unique_ptr<vk::Fence> > m_inFlightFences{ vk::SwapChain::MAX_FRAMES_IN_FLIGHT };
	//	std::vector< std::unique_ptr<vk::Semaphore> > m_imageAvailableSemaphores{ vk::SwapChain::MAX_FRAMES_IN_FLIGHT };
	//	std::vector< std::unique_ptr<vk::Semaphore> > m_renderFinishedSemaphores{ vk::SwapChain::MAX_FRAMES_IN_FLIGHT };

	//	/// Systems
	//	std::unique_ptr < vk::DescriptorSetLayout > m_globalDescSetLayout;
	//	// basic sys
	//	bool m_BasicSysOn = false;
	//	std::unique_ptr<BasicRenderSys> m_basicRenderSys;
	//	std::unique_ptr < vk::DescriptorSetLayout > m_basicDescSetLayout;
	//	
	//	// gltf test
	//	bool m_gltfSysOn = true;
	//	std::unique_ptr<glTFRenderSys> m_gltfRenderSys;
	//	// this is for the pipelineLayout, the one in the model is for the descriptorSet,should be same as in the molde material
	//	// systems who call model drawing function should use it ;
	//	std::unique_ptr < vk::DescriptorSetLayout > m_materialDescSetLayout;
	//	
	//	// DebugSys sys
	//	bool m_DeugSysOn = false;
	//	std::unique_ptr<DebugSys> m_DebugSys;
	//	// shadow sys
	//	bool m_ShadowMapSysOn = true;
	//	std::unique_ptr<ShadowMappingSys> m_shadowMapSys;

	//	uint32_t m_currentFrame = 0;
	//	GlobalUBO m_ubo;

	};
}



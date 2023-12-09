#include "pch.h"
#include "Renderer.h"

namespace Alalba
{

//	Renderer::Renderer(Scene& scene)
//		:m_scene(scene)
//	{
//		Application& app = Application::Get();
//		const vk::Device& device = app.GetDevice();
//
//		m_allocator.reset(new vk::Allocator(device, app.GetVulkanInstance(), "Renderer Allocator"));
//		
//		m_pipelineCache = vk::PipelineCache::Builder(device)
//			.SetTag("Rendering PipelineCache")
//			.Build();
//
//		m_swapChain = vk::SwapChain::Builder(device, app.GetSurface())
//			.SetPresentMode(VK_PRESENT_MODE_MAILBOX_KHR)
//			.SetImgSharingMode(VK_SHARING_MODE_EXCLUSIVE)
//			.Build();
//
//		m_commandPool = vk::CommandPool::Builder(device)
//			.SetTag("Renderer CmdPool")
//			//.SetFlags(VK_COMMAND_POOL_CREATE_TRANSIENT_BIT | VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT)
//			.SetFlags(VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT)
//			.SetQFamily(device.GetGraphicsQ().GetFamily())
//			.Build();
//		m_commandBuffers = vk::CommandBuffers::Allocator(device, *m_commandPool)
//			.SetTag("CmdBuffers4Graphics")
//			.OneTimeSubmit(true)
//			.SetSize(3) // one for each image in swapchain
//			.Allocate();
//		
//		for (int i = 0; i < vk::SwapChain::MAX_FRAMES_IN_FLIGHT; i++)
//		{
//			m_depthImages[i] = vk::Image::Builder(device, *m_allocator)
//				.SetTag("DepthImage")
//				.SetImgType(VK_IMAGE_TYPE_2D)
//				.SetSharingMode(VK_SHARING_MODE_EXCLUSIVE)
//				.SetImageFormat(device.FindSupportedFormat(
//					{ VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT },
//					VK_IMAGE_TILING_OPTIMAL,
//					VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
//				))// this should be compatible with framebuffer
//				.SetImageTiling(VK_IMAGE_TILING_OPTIMAL)
//				.SetUsageFlags(VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT)
//				.SetImgExtent(VkExtent3D{ m_swapChain->GetExtent().width, m_swapChain->GetExtent().height,1 })
//				.Build();
//
//			m_depthImages[i]->TransitionImageLayout(*m_commandPool, device.GetGraphicsQ(),
//				VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
//
//			m_depthImageViews[i] = vk::ImageView::Builder(device, *m_depthImages[i])
//				.SetTag("depthImageView")
//				.SetViewType(VK_IMAGE_VIEW_TYPE_2D)
//				.SetSubresourceAspectFlags(VK_IMAGE_ASPECT_DEPTH_BIT)
//				.SetFormat(m_depthImages[i]->GetFormat())
//				.Build();
//		}
//
//		m_renderPass = vk::RenderPass::Builder(device)
//			.PushColorAttachment(m_swapChain->GetFormat(), VK_ATTACHMENT_LOAD_OP_CLEAR, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR)
//			.PushDepthAttachment(m_depthImages[0]->GetFormat(), VK_ATTACHMENT_LOAD_OP_CLEAR, VK_IMAGE_LAYOUT_UNDEFINED)
//			// there is an image layout the transition at the start of the render pass and at the end of the render pass
//			// but the former does not occur at the right time
//			// https://vulkan-tutorial.com/Drawing_a_triangle/Drawing/Rendering_and_presentation
//			.AddDependency(VK_SUBPASS_EXTERNAL,VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, 0, 0,VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT)
//			.AddDependency(VK_SUBPASS_EXTERNAL, VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT, 0, 0, VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT, VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT)
//			.Build();
//
//		m_globalDescPool = vk::DescriptorPool::Builder(device)
//			.SetTag("Global Descriptor Pool")
//			.SetMaxSets(vk::SwapChain::MAX_FRAMES_IN_FLIGHT)
//			.AddPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, m_swapChain->GetImgCount())
//			// 1: for shadow map
//			.AddPoolSize(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, m_swapChain->GetImgCount())
//			.Build();
//
//		m_globalDescSetLayout = vk::DescriptorSetLayout::Builder(device)
//			// 0 : is bingding index of the binding slot in the set
//			.AddBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT)
//			// 1: for shadow map
//			.AddBinding(1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT)
//			.SetTag("Global Descriptor Set Layout")
//			.Build();
//
//		for (int i = 0; i < vk::SwapChain::MAX_FRAMES_IN_FLIGHT; i++)
//		{
//			std::string str_int = std::to_string(i);
//			std::string tag = std::string{ "Frame buffer for Swapchain" } + str_int;
//			m_frameBuffers[i] = vk::FrameBuffer::Builder(device, *m_renderPass)
//				.SetTag(tag)
//				.SetWidthHeight(m_swapChain->GetExtent().width, m_swapChain->GetExtent().height)
//				.PushAttachment(m_swapChain->GetImageView(i))
//				.PushAttachment(*m_depthImageViews[i]) // TODO : FOR NOW depth attachment must be added at the end of attachment list
//				.Build();
//
//			m_inFlightFences[i] =
//				vk::Fence::Builder(device)
//				.SetTag("InFlightFence " + std::to_string(i))
//				.Signaled(true)
//				.Build();
//
//			m_imageAvailableSemaphores[i] = vk::Semaphore::Builder(device)
//				.SetTag("imageAvailableSemaphore " + std::to_string(i))
//				.Build();
//
//			m_renderFinishedSemaphores[i] = vk::Semaphore::Builder(device)
//				.SetTag("renderFinishedSemaphore " + std::to_string(i))
//				.Build();
//
//			m_globalUniformbuffers[i] = vk::Buffer::Builder(device, *m_allocator)
//				.SetTag("Global Uniform Buffer" + std::to_string(i))
//				.SetSize(sizeof(GlobalUBO))
//				.SetUsage(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT)
//				.SetVmaUsage(VMA_MEMORY_USAGE_CPU_TO_GPU)
//				.Build();
//
//			m_globalUniformbuffers[i]->MapMemory();
//
//			m_GlobalDescriptorSets[i] =
//				vk::DescriptorSet::Allocator(device, *m_globalDescPool)
//				.SetTag("Global Descritor Set " + std::to_string(i))
//				.SetDescSetLayout(*m_globalDescSetLayout)
//				.Allocate();
//	/*		m_GlobalDescriptorSets[i]->
//				BindDescriptor(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 0, *m_globalUniformbuffers[i], 0, sizeof(GlobalUBO))
//				.UpdateDescriptors();*/
//		}
//
/////  Rendering systems
//		//0. basic
//		//m_basicDescSetLayout = vk::DescriptorSetLayout::Builder(device)
//		//	// 0 : is bingding index of the binding slot in the set
//		//	.AddBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT)
//		//	.AddBinding(1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT)
//		//	.SetTag("basic descriptor Set Layout")
//		//	.Build();
//		//std::vector<const vk::DescriptorSetLayout*> basicDescriptorSetLayout =
//		//{
//		//	m_globalDescSetLayout.get(),
//		//	m_basicDescSetLayout.get()
//		//};
//		//m_basicRenderSys = std::make_unique<BasicRenderSys>(scene, *m_renderPass, basicDescriptorSetLayout, *m_pipelineCache);
//
//		
//		m_materialDescSetLayout = vk::DescriptorSetLayout::Builder(device)
//			// 0 : is bingding index of the binding slot in the set
//			.AddBinding(0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT)
//			.AddBinding(1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT)
//			.AddBinding(2, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT)
//			.AddBinding(3, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT)
//			.SetTag("gltf descriptor Set Layout")
//			.Build();
//		
//		// 0. ShadowMap: OFF SCREEN
//		std::vector<const vk::DescriptorSetLayout*> shadowDescriptorSetLayout =
//		{
//			m_globalDescSetLayout.get(),
//			m_materialDescSetLayout.get() // for model drawing 
//		};
//		m_shadowMapSys = std::make_unique<ShadowMappingSys>(scene, shadowDescriptorSetLayout);
//
//		// 1. DebugSys for shadow mapp
//		m_DebugSys = std::make_unique<DebugSys>(*m_renderPass, VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL, m_shadowMapSys->GetImageView(0), m_shadowMapSys->GetSampler(0));
//
//		/// 2. gltf test
//		std::vector<const vk::DescriptorSetLayout*> gltfDescriptorSetLayout =
//		{
//			m_globalDescSetLayout.get(),
//			m_materialDescSetLayout.get()
//		};
//		for (int i = 0; i < vk::SwapChain::MAX_FRAMES_IN_FLIGHT; i++)
//		{
//			m_GlobalDescriptorSets[i]->
//				BindDescriptor(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 0, *m_globalUniformbuffers[i], 0, sizeof(GlobalUBO))
//				.BindDescriptor(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1, m_shadowMapSys->GetSampler(i), m_shadowMapSys->GetImageView(i), VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL)
//				.UpdateDescriptors();
//		}
//		m_gltfRenderSys = std::make_unique<glTFRenderSys>(scene, *m_renderPass, gltfDescriptorSetLayout, *m_pipelineCache);
//	
//
//		// ui init
//		app.m_ui = new UIOverlay(*m_renderPass);
//
//		PrepareCommandBuffers();
//	}
//	void Renderer::Shutdown()
//	{
//		const vk::Device& device = Application::Get().GetDevice();
//		device.WaitIdle();
//	
//		//m_basicDescSetLayout->Clean();
//		//m_basicRenderSys->ShutDown();
//
//		m_shadowMapSys->ShutDown();
//		m_DebugSys->ShutDown();
//		m_gltfRenderSys->ShutDown();
//
//
//		m_pipelineCache->Clean();
//		m_swapChain->Clean();
//
//		m_renderPass->Clean();
//		for (auto& framebuffer : m_frameBuffers)
//			framebuffer->Clean();
//		
//		for (auto& depthImage : m_depthImages)
//			depthImage->Clean();
//		for (auto& depthImageView : m_depthImageViews)
//			depthImageView->Clean();
//
//		m_commandBuffers->Clean();
//		m_commandPool->Clean();
//
//		for (int i = 0; i < vk::SwapChain::MAX_FRAMES_IN_FLIGHT; i++)
//		{
//			m_inFlightFences[i]->Clean();
//			m_imageAvailableSemaphores[i]->Clean();
//			m_renderFinishedSemaphores[i]->Clean();
//			m_globalUniformbuffers[i]->Clean();
//			m_GlobalDescriptorSets[i]->Clean();
//		}
//
//		m_globalDescPool->Clean();
//
//		/// rendering systems
//		// clean descriptor set layouts
//		m_globalDescSetLayout->Clean();
////		m_basicDescSetLayout->Clean();
//		m_materialDescSetLayout->Clean();
//
//		m_allocator->Clean();
//	}
//	void Renderer::Resize()
//	{
//		Application& app = Application::Get();
//		const vk::Device& device = Application::Get().GetDevice();
//		device.WaitIdle();
//		// clean old framebuffers , depth image , depthimage view and swapchain
//		for (int i = 0; i < vk::SwapChain::MAX_FRAMES_IN_FLIGHT; i++)
//		{
//			m_frameBuffers[i]->Clean();
//		}
//		for (auto& depthImage : m_depthImages)
//			depthImage->Clean();
//		for (auto& depthImageView : m_depthImageViews)
//			depthImageView->Clean();
//		m_swapChain->Clean();
//
//		// recreate framebuffers , depth image , depthimage view and swapchain
//		m_swapChain.reset(new vk::SwapChain(device, app.GetSurface(), VK_PRESENT_MODE_MAILBOX_KHR, VK_SHARING_MODE_EXCLUSIVE));
//
//		
//
//		for (int i = 0; i < vk::SwapChain::MAX_FRAMES_IN_FLIGHT; i++)
//		{
//			m_depthImages[i].reset(new vk::Image(device, *m_allocator, VK_IMAGE_TYPE_2D,
//				VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
//				VkExtent3D{ m_swapChain->GetExtent().width, m_swapChain->GetExtent().height,1 },
//				device.FindSupportedFormat(
//					{ VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT },
//					VK_IMAGE_TILING_OPTIMAL,
//					VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
//				),
//				VK_IMAGE_TILING_OPTIMAL,
//				VK_SHARING_MODE_EXCLUSIVE,
//				"Recreated depth image"
//			));
//
//			m_depthImageViews[i].reset(new vk::ImageView(device, m_depthImages[i]->Handle(),
//				VK_IMAGE_ASPECT_DEPTH_BIT, m_depthImages[i]->GetFormat(),
//				VK_IMAGE_VIEW_TYPE_2D, "Recreated Depth ImageView"
//			));
//			std::vector<const vk::ImageView*> attachments;
//			attachments.push_back(&(m_swapChain->GetImageView(i)));
//			attachments.push_back(m_depthImageViews[i].get());
//
//			m_frameBuffers[i].reset(new vk::FrameBuffer(
//				device, *m_renderPass,
//				attachments, m_swapChain->GetExtent().width, m_swapChain->GetExtent().height,
//				"resized Framebuffer"));
//		}
//
//		PrepareCommandBuffers();
//
//		// SRS - Recreate fences in case number of swapchain images has changed on resize
//		for (int i = 0; i < vk::SwapChain::MAX_FRAMES_IN_FLIGHT; i++)
//		{
//			m_inFlightFences[i]->Clean();
//			m_inFlightFences[i] =
//				vk::Fence::Builder(device)
//				.SetTag("Resize InFlightFence " + std::to_string(i))
//				.Signaled(true)
//				.Build();
//		}
//		// After recreate SwapChain, the first available image index is 0 (get by vkAcquireNextImageKHR)
//		// to keep index coincident, MUST rest m_currentFrame
//		m_currentFrame = 0;
//
//	}
//	void Renderer::PrepareCommandBuffers()
//	{
//	
//		for (int i = 0; i < vk::SwapChain::MAX_FRAMES_IN_FLIGHT; i++)
//		{
//			UpdateCommandBuffer(i);
//		}
//	}
//
//	void Renderer::UpdateCommandBuffer(uint32_t currentFrame)
//	{
//		vk::CommandBuffers& cmdBuffers = (*m_commandBuffers);
//
//		cmdBuffers.BeginRecording(currentFrame);
//		{
//			/// Off Screen sys have their own renderpass
//			// off  shadow mapp	
//			m_shadowMapSys->GenerateShadowMapp(cmdBuffers, currentFrame);
//
//
//			///  On screen using renderer's renderpass
//			if (m_DeugSysOn)
//				m_DebugSys->BuildCommandBuffer(*m_renderPass, *m_frameBuffers[currentFrame], m_swapChain->GetExtent(), *m_commandBuffers, currentFrame);
//
//			/// rendering sys
//			if (m_gltfSysOn)
//				m_gltfRenderSys->BuildCommandBuffer(*m_renderPass, *m_frameBuffers[currentFrame], m_swapChain->GetExtent(), *m_GlobalDescriptorSets[currentFrame], *m_commandBuffers, currentFrame);
//		}
//		cmdBuffers.EndRecording(currentFrame);
//
//	}
//
//	void Renderer::Update(Scene& scene)
//	{
//		// update camera
//		auto view = scene.GetAllEntitiesWith<CamComponent>();
//		for (auto e : view)
//		{
//			Entity entity = { e, &scene};
//			// camera
//			auto& camera = entity.GetComponent<CamComponent>().m_Camera;
//			m_ubo.view = camera.GetViewMatrix();
//			m_ubo.proj = camera.GetProjectionMatrix();
//			m_ubo.camPos = glm::vec4(camera.GetPosition(),1.0);
//		}
//
//		// update light
//		auto viewlight = scene.GetAllEntitiesWith<PointLightComponent>();
//		for (auto e : viewlight)
//		{
//			Entity entity = { e, &scene };
//
//			auto& position = entity.GetComponent<PointLightComponent>().LightPosition;
//			auto& color = entity.GetComponent<PointLightComponent>().LightColor;
//			m_ubo.lightcolor = color;
//			m_ubo.lightposition = position;
//			m_ubo.lightproj = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
//			m_ubo.lightproj[1][1] *= -1;
//			m_ubo.lightview = glm::lookAt(glm::vec3(position), glm::vec3(0.0f), glm::vec3(0, 1, 0));
//		}
//
//		memcpy(m_globalUniformbuffers[m_currentFrame]->Mapped(), &m_ubo, sizeof(m_ubo));
//		m_globalUniformbuffers[m_currentFrame]->Flush();
//
//		//
//		//m_basicRenderSys->Update(scene);
//
//		m_shadowMapSys->Update(scene, m_currentFrame);
//		m_DebugSys->Update();
//		m_gltfRenderSys->Update();
//
//		/////todo: update UI
////********** for test**************
//		Application& app = Application::Get();
//		app.m_ui->NewFrame();
//		//if (app.m_ui->BufferUpdated() && app.m_ui->visiable)
//		//{
//		//	PrepareCommandBuffer();
//		//}
//		//***************************
//	}
//
//	void Renderer::DrawFrame(Scene& scene)
//	{
//		Application& app = Application::Get();
//		const vk::Device& device = app.GetDevice();
//
//		m_inFlightFences[m_currentFrame]->Wait(UINT64_MAX);
//
///// Presentation queue: siganl semaphore for graphics queue
//		VkResult result = vkAcquireNextImageKHR(device.Handle(), m_swapChain->Handle(), UINT64_MAX, m_imageAvailableSemaphores[m_currentFrame]->Handle(), VK_NULL_HANDLE, &m_currentFrame);
//
//		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)
//		{
//			Resize();
//			return;
//		}
//		else
//		{
//			ALALBA_ASSERT(result == VK_SUCCESS, "Acquire Next Image Failed");
//		}
//		// update ubo
//		Update(scene);
//
//		
///// fence must be reset, before gpu can signal it again
//		m_inFlightFences[m_currentFrame]->Reset();
//		if (app.m_ui->BufferUpdated() && app.m_ui->visiable)
//		{
//			UpdateCommandBuffer(m_currentFrame);
//		
//		}
//		// TODO: abstract to a new submit method
//		
//		// submit a command buffer batch
//		VkCommandBuffer commandBuffers[]{ (*m_commandBuffers)[m_currentFrame] };
//		VkSemaphore waitSemaphores[] = { m_imageAvailableSemaphores[m_currentFrame]->Handle() };
//		VkSemaphore signalSemaphores[] = { m_renderFinishedSemaphores[m_currentFrame]->Handle() };
//		VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
//		
///// graphics queue  		
//		/// graphics queue waits on imageAvailable semaphore signaled by presentation queue
//		/// After graphics queue finished, it will signal fence to cpu, and renderFinished to presentation queue
//		// waitStages VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT: new image needed only when command start COLOR_ATTACHMENT_OUTPUT stage
//		VkSubmitInfo submitInfo = {};
//		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
//		submitInfo.waitSemaphoreCount = 1;
//		submitInfo.pWaitSemaphores = waitSemaphores;
//		submitInfo.pWaitDstStageMask = waitStages;
//		submitInfo.signalSemaphoreCount = 1;
//		submitInfo.pSignalSemaphores = signalSemaphores;
//		submitInfo.commandBufferCount = 1;
//		submitInfo.pCommandBuffers = commandBuffers;
//		VkResult err;
//		err = vkQueueSubmit(device.GetGraphicsQ().Handle(),
//			1, &submitInfo, m_inFlightFences[m_currentFrame]->Handle());
//		ALALBA_ASSERT(err == VK_SUCCESS, "Q submit failed");
//	
//
///// prensent queue 
//		/// wait on signal from graphics queue
//		// TODO: abstract to a new present method
//		VkPresentInfoKHR presentInfo{};
//		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
//		presentInfo.waitSemaphoreCount = 1;
//		presentInfo.pWaitSemaphores = signalSemaphores;
//
//		VkSwapchainKHR swapChains[] = { m_swapChain->Handle() };
//		presentInfo.swapchainCount = 1;
//		presentInfo.pSwapchains = swapChains;
//		presentInfo.pImageIndices = &m_currentFrame;
//		presentInfo.pResults = nullptr; // Optional
//
//		result = vkQueuePresentKHR(device.GetGraphicsQ().Handle(), &presentInfo);
//		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)
//		{
//			Resize();
//			return;
//		}
//		else
//		{
//			ALALBA_ASSERT(result == VK_SUCCESS, "Queue Present Failed");
//		}
//		m_currentFrame = (m_currentFrame + 1) % vk::SwapChain::MAX_FRAMES_IN_FLIGHT;
//
//	}
}

#include "BreakpointListUI.h"
#include <imgui/imgui.h>

#include <ghc/filesystem.hpp>

namespace ed
{
	void DebugBreakpointListUI::OnEvent(const SDL_Event& e)
	{}
	void DebugBreakpointListUI::Update(float delta)
	{
		const auto& bkpts = m_data->Debugger.GetBreakpointList();
		auto bkptStates = m_data->Debugger.GetBreakpointStateList();
		bool isEnabled = false;

		ImGui::Columns(4);
		
		ImGui::Text("File");
		ImGui::NextColumn();
		ImGui::Text("Enabled");
		ImGui::NextColumn();
		ImGui::Text("Condition");
		ImGui::NextColumn();
		ImGui::Text("Line");
		ImGui::NextColumn();

		for (const auto& bkpt : bkpts) {
			std::string fileNameStr = ghc::filesystem::path(bkpt.first).filename();
			const char* fileName = fileNameStr.c_str();
			for (int i = 0; i < bkpt.second.size(); i++) {
				ImGui::Separator();

				ImGui::Text(fileName);
				ImGui::NextColumn();

				const sd::Breakpoint& b = bkpt.second[i];
				isEnabled = bkptStates[bkpt.first][i];
				if (ImGui::Checkbox(("##bkpt_state" + std::to_string(i)).c_str(), &isEnabled))
					m_data->Debugger.SetBreakpointEnabled(bkpt.first, b.Line, isEnabled);
				ImGui::NextColumn();

				ImGui::Text(b.Condition.c_str());
				ImGui::NextColumn();
				ImGui::Text("%d", b.Line);
				ImGui::NextColumn();
			}
		}
		ImGui::Columns();
	}
}
#include "UILayout/ChooseDS.h"




DSType strToDSType(std::string str) {
	if (str == "Lists - Singly Linked List") {
		return DSType::SINGLY_LINKED_LIST;
	} else if (str == "Hash Table - Linear Probing") {
		return DSType::HASH_TABLE;
	} else if (str == "Trees - AVL Tree") {
		return DSType::AVL_TREE;
	} else if (str == "Trees - Trie") {
		return DSType::TRIE_TREE;
	} else if (str == "Graphs - Minimum Spanning Tree (Prim\'s algorithm)") {
		return DSType::MST_PRIM_GRAPH;
	} else if (str == "Graphs - Shortest Path (Dijkstra\'s algorithm)") {
		return DSType::DIJKSTRA_GRAPH;
	}
	return DSType::DEFAULT;
}

std::string getDataFileName(std::string ds_selection_str) {
	DSType chosenDSType = strToDSType(ds_selection_str);
	switch (chosenDSType) {
	case DSType::SINGLY_LINKED_LIST:
		return "SLL.txt";
		break;
	case DSType::HASH_TABLE:
		return "HashTable.txt";
		break;
	case DSType::AVL_TREE:
		return "AVL.txt";
		break;
	case DSType::TRIE_TREE:
		return "Trie.txt";
		break;
	case DSType::MST_PRIM_GRAPH:
	case DSType::DIJKSTRA_GRAPH:
		return "Graph.txt";
		break;
	default:
		return "";
		break;
	}
}

std::string getLongestDS_Str() {
	float maxStringSize = 0; std::string longestString = "";
	for (const auto& DS_string : ALL_DS_LIST) {
		float textSize = ImGui::CalcTextSize(DS_string.c_str()).x;
		if (textSize > maxStringSize) {
			maxStringSize = textSize;
			longestString = DS_string;
		}
	}
	return longestString;
}





// REMEMBER:
// Drawing SFML: The center of the window is now (0, 0) coordinates
// Drawing GUI: The top-left of the window is (0, 0) coordinates
// Display settings menu screen
void Program::initChooseDSMenuScreen() {
	allowDragCanvas = false;
}



void Program::displayChooseDSMenuScreenSFML() {

}



void Program::displayChooseDSMenuScreenGUI() {
	allowDragCanvas = false;

	// Get the current window size
	sf::Vector2u sfml_window_size = window.getSize();

	// Show the demo window
	// ImGui::ShowDemoWindow();

	// Show the example window
	// ImGui::Begin("Hello, world!",
	// 	nullptr
	// 	// ImGuiWindowFlags_NoCollapse
	// 	// ImGuiWindowFlags_NoBackground
	// );
	// ImGui::Button("Look at this pretty button");
	// // char buf[25];
	// // ImGui::InputText("string", buf, IM_COUNTOF(buf));
	// ImGui::InputText("string", buf, 25);
	// // float f;
	// ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

	// const char* items[] = { "Option 1", "Option 2", "Option 3", "Option 4" };
	// static int current_item = 0;
	// if (ImGui::BeginCombo("##mycombo", items[current_item])) { // Pass the "current" item name as the preview
	// 	for (int n = 0; n < IM_ARRAYSIZE(items); n++) {
	// 		bool is_selected = (current_item == n);
	// 		if (ImGui::Selectable(items[n], is_selected)) {
	// 			current_item = n;
	// 		}

	// 		// Set the initial focus when opening the combo (scrolling + keyboard navigation)
	// 		if (is_selected) {
	// 			ImGui::SetItemDefaultFocus();
	// 		}
	// 	}
	// 	ImGui::EndCombo();
	// }
	// ImGui::End();


	// sf::Vector2u btnSize, btnPosition;
	// btnSize = sf::Vector2u(120, 40);
	// btnPosition = sfml_window_size / 2U;
	// ImGui::SetNextWindowPos(btnPosition - btnSize / 2U);
	// ImGui::Begin("StartBtn",
	// 	nullptr,
	// 	ImGuiWindowFlags_NoTitleBar |
	// 	ImGuiWindowFlags_NoCollapse |
	// 	ImGuiWindowFlags_NoResize |
	// 	ImGuiWindowFlags_NoMove |
	// 	ImGuiWindowFlags_NoBackground |
	// 	ImGuiWindowFlags_NoScrollbar
	// );

	// if (ImGui::Button("Start", btnSize)) { // clicked
	// 	printf("%s %f\nButton clicked! \n", buf, f);
	// }
	// ImGui::End();


	// btnSize = sf::Vector2u(120, 40);
	// btnPosition = sfml_window_size / 2U + sf::Vector2u(0, 60);
	// ImGui::SetNextWindowPos(btnPosition - btnSize / 2U);
	// ImGui::Begin("ChooseDSBtn",
	// 	nullptr,
	// 	ImGuiWindowFlags_NoTitleBar |
	// 	ImGuiWindowFlags_NoCollapse |
	// 	ImGuiWindowFlags_NoResize |
	// 	ImGuiWindowFlags_NoMove |
	// 	ImGuiWindowFlags_NoBackground |
	// 	ImGuiWindowFlags_NoScrollbar
	// );

	// if (ImGui::Button("ChooseDS", btnSize)) { // clicked
	// 	printf("Program exited.\n");
	// 	window.close();
	// }
	// ImGui::End();


	// btnSize = sf::Vector2u(120, 40);
	// btnPosition = sfml_window_size / 2U + sf::Vector2u(0, 120);
	// ImGui::SetNextWindowPos(btnPosition - btnSize / 2U);
	// ImGui::Begin("QuitBtn",
	// 	nullptr,
	// 	ImGuiWindowFlags_NoTitleBar |
	// 	ImGuiWindowFlags_NoCollapse |
	// 	ImGuiWindowFlags_NoResize |
	// 	ImGuiWindowFlags_NoMove |
	// 	ImGuiWindowFlags_NoBackground |
	// 	ImGuiWindowFlags_NoScrollbar
	// );

	// if (ImGui::Button("Quit", btnSize)) { // clicked
	// 	printf("Program exited.\n");
	// 	window.close();
	// }
	// ImGui::End();



	sf::Vector2u gui_window_size(640, 500);
	ImVec2 Im_gui_window_size = sf::Vector2f(gui_window_size);
	ImGui::SetNextWindowPos(sfml_window_size / 2U - gui_window_size / 2U);
	ImGui::SetNextWindowSize(gui_window_size, ImGuiCond_Always);
	// ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
	ImGui::Begin("Data Structure Selection",
		nullptr,
		ImGuiWindowFlags_NoCollapse |
		// ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoResize |
		// ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoMove
	);
	// ImGui::PopStyleColor();

	if (ImGui::Button("Go back")) {
		programState = ProgramState::MAIN_MENU;
		std::cout << "-- Go to main menu." << std::endl;
		resizeView();
	}

	std::string titleText = "Choose a data structure to visualize:";
	ImVec2 textSize = ImGui::CalcTextSize(titleText.c_str());
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + Im_gui_window_size.x/2.f - textSize.x/2.f);
	ImGui::Text("%s", titleText.c_str());

	// Get width of combo before drawing
	// float DSComboWidth = ImGui::CalcTextSize(getLongestDS_Str().c_str()).x + stylePtr->FramePadding.x * 2.0f;
	float DSComboWidth = ImGui::CalcTextSize(getLongestDS_Str().c_str()).x * 1.2;
	ImGui::SetNextItemWidth(DSComboWidth);
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + Im_gui_window_size.x/2.f - DSComboWidth/2);

	// Draw combo (dropdown list)
	const char* DSOptions[] = ALL_DS_TYPE_LIST;
	const std::vector<std::string> DSVectors = ALL_DS_TYPE_LIST;
	static int current_DS_item = 0;
	// ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(173.f/255, 216.f/255, 230.f/255, 1.f));
	if (ImGui::BeginCombo("##DS_combo", DSOptions[current_DS_item])) { // Pass the "current" item name as the preview
		for (int n = 0; n < IM_ARRAYSIZE(DSOptions); n++) {
			bool is_selected = (current_DS_item == n);
			if (ImGui::Selectable(DSOptions[n], is_selected)) {
				current_DS_item = n;
			}

			// Set the initial focus when opening the combo (scrolling + keyboard navigation)
			if (is_selected) {
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}
	// ImGui::PopStyleColor();

	// --- Selected DS type ---
	DSType chosenDSType = strToDSType(DSVectors[current_DS_item]);


	// ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();
	ImGui::Dummy(ImVec2(10, 10)); ImGui::Separator(); ImGui::Dummy(ImVec2(10, 10));


	titleText = "Choose initial starting data:";
	textSize = ImGui::CalcTextSize(titleText.c_str());
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + Im_gui_window_size.x/2.f - textSize.x/2.f);
	ImGui::Text("%s", titleText.c_str());

	ImGui::BeginGroup();
	// Data init method (empty, random, file, string)
	static int dataInitOption = DATA_INIT_EMPTY; // State variable to hold the selected option's value
	// Graph data init method
	static GraphReader::GraphInitMethod graphInitOption = GraphReader::GraphInitMethod::ADJ_MATRIX; // State variable to hold the selected option's value

	ImGui::RadioButton("Empty data", &dataInitOption, DATA_INIT_EMPTY); // Value 0
	ImGui::SameLine();
	ImGui::RadioButton("Randomized data", &dataInitOption, DATA_INIT_RANDOMIZED); // Value 1
	ImGui::SameLine();
	ImGui::RadioButton("Enter custom data", &dataInitOption, DATA_INIT_CUSTOM); // Value 2
	ImGui::SameLine();
	ImGui::RadioButton("Data from \".txt\" file", &dataInitOption, DATA_INIT_FROM_FILE); // Value 3

	bool invalidDataCustom = false; // To print error messages when invalid data

	///// --- MUST FINISH ALL 6 DATA STRUCTURES --- /////
	if (dataInitOption == DATA_INIT_EMPTY) {
		switch (chosenDSType) {
		case DSType::HASH_TABLE:
			// Input HashTable size and modulo integer
			ImGui::Dummy(ImVec2(ImGui::GetTextLineHeight(), ImGui::GetTextLineHeight()));
			ImGui::InputScalar(SIZE_INPUT_WARNING_STRING.c_str(), 
				ImGuiDataType_U32, &initHashTableSizeBuf);
			initHashTableSizeBuf = std::min(std::max(initHashTableSizeBuf, 2U), MAX_INIT_HASHTABLE_SIZE); // Clamp table size
			ImGui::InputScalar(MODULO_INPUT_WARNING_STRING.c_str(), 
				ImGuiDataType_U32, &initHashTableModuloBuf);
			initHashTableModuloBuf = std::min(std::max(initHashTableModuloBuf, 2U), MAX_INIT_HASHTABLE_MODULO); // Clamp table modulo for hash function
			break;
		case DSType::AVL_TREE:
			break;
		case DSType::TRIE_TREE:
			break;
		case DSType::MST_PRIM_GRAPH:
			break;
		case DSType::DIJKSTRA_GRAPH:
			break;
		default:
			break;
		}
	} else if (dataInitOption == DATA_INIT_RANDOMIZED) {
		switch (chosenDSType) {
		case DSType::HASH_TABLE:
			// Input HashTable size and modulo integer
			ImGui::Dummy(ImVec2(ImGui::GetTextLineHeight(), ImGui::GetTextLineHeight()));
			ImGui::InputScalar(SIZE_INPUT_WARNING_STRING.c_str(), 
				ImGuiDataType_U32, &initHashTableSizeBuf);
			initHashTableSizeBuf = std::min(std::max(initHashTableSizeBuf, 2U), MAX_INIT_HASHTABLE_SIZE); // Clamp table size
			ImGui::InputScalar(MODULO_INPUT_WARNING_STRING.c_str(), 
				ImGuiDataType_U32, &initHashTableModuloBuf);
			initHashTableModuloBuf = std::min(std::max(initHashTableModuloBuf, 2U), MAX_INIT_HASHTABLE_MODULO); // Clamp table modulo for hash function
			break;
		case DSType::AVL_TREE:
			break;
		case DSType::TRIE_TREE:
			break;
		case DSType::MST_PRIM_GRAPH:
			break;
		case DSType::DIJKSTRA_GRAPH:
			break;
		default:
			break;
		}
	} else if (dataInitOption == DATA_INIT_CUSTOM) {
		///// --- MUST FINISH ALL 6 DATA STRUCTURES --- /////
		std::string dataString; // String of entered data
		switch (chosenDSType) {
		case DSType::SINGLY_LINKED_LIST:
			ImGui::InputTextMultiline("##CustomDataSLL", customDataSLLBuf, CUSTOM_DATA_BUF_SIZE, ImVec2(-1.0f, 200.0f));
			dataString = std::string(customDataSLLBuf);
			invalidDataCustom = !validDataSLLString(dataString);
			break;
		case DSType::HASH_TABLE:
			ImGui::InputTextMultiline("##CustomDataHash", customDataHashBuf, CUSTOM_DATA_BUF_SIZE, ImVec2(-1.0f, 200.0f));
			dataString = std::string(customDataHashBuf);
			invalidDataCustom = !validDataHashTableString(dataString);
			break;
		case DSType::AVL_TREE:
			ImGui::InputTextMultiline("##CustomDataAVL", customDataAVLBuf, CUSTOM_DATA_BUF_SIZE, ImVec2(-1.0f, 200.0f));
			dataString = std::string(customDataAVLBuf);
			invalidDataCustom = !validDataAVLString(dataString);
			break;
		case DSType::TRIE_TREE:
			ImGui::InputTextMultiline("##CustomDataTrie", customDataTrieBuf, CUSTOM_DATA_BUF_SIZE, ImVec2(-1.0f, 200.0f));
			dataString = std::string(customDataTrieBuf);
			invalidDataCustom = !validDataTrieString(dataString);
			break;
		case DSType::MST_PRIM_GRAPH:
			ImGui::RadioButton("Adjacency Matrix", (int*)&graphInitOption, (int)GraphReader::GraphInitMethod::ADJ_MATRIX); // Value 0
			ImGui::SameLine();
			ImGui::RadioButton("Adjacency List", (int*)&graphInitOption, (int)GraphReader::GraphInitMethod::ADJ_LIST); // Value 1
			ImGui::SameLine();
			ImGui::RadioButton("Edge List", (int*)&graphInitOption, (int)GraphReader::GraphInitMethod::EDGE_LIST); // Value 2

			ImGui::InputTextMultiline("##CustomDataMST", customDataMSTPrimBuf, CUSTOM_DATA_BUF_SIZE, ImVec2(-1.0f, 200.0f));
			
			dataString = std::string(customDataMSTPrimBuf);
			invalidDataCustom = !GraphReader::validDataGraphString(dataString, graphInitOption);
			break;
		case DSType::DIJKSTRA_GRAPH:
			ImGui::RadioButton("Adjacency Matrix", (int*)&graphInitOption, (int)GraphReader::GraphInitMethod::ADJ_MATRIX); // Value 0
			ImGui::SameLine();
			ImGui::RadioButton("Adjacency List", (int*)&graphInitOption, (int)GraphReader::GraphInitMethod::ADJ_LIST); // Value 1
			ImGui::SameLine();
			ImGui::RadioButton("Edge List", (int*)&graphInitOption, (int)GraphReader::GraphInitMethod::EDGE_LIST); // Value 2

			ImGui::InputTextMultiline("##CustomDataDijkstra", customDataDijkstraBuf, CUSTOM_DATA_BUF_SIZE, ImVec2(-1.0f, 200.0f));
			
			dataString = std::string(customDataDijkstraBuf);
			invalidDataCustom = !GraphReader::validDataGraphString(dataString, graphInitOption);
			break;
		default:
			break;
		}
	} else if (dataInitOption == DATA_INIT_FROM_FILE) {
		std::string dataFileName = getDataFileName(DSVectors[current_DS_item]);

		switch (chosenDSType) {
		case DSType::MST_PRIM_GRAPH:
		case DSType::DIJKSTRA_GRAPH:
			ImGui::RadioButton("Adjacency Matrix", (int*)&graphInitOption, (int)GraphReader::GraphInitMethod::ADJ_MATRIX); // Value 0
			ImGui::SameLine();
			ImGui::RadioButton("Adjacency List", (int*)&graphInitOption, (int)GraphReader::GraphInitMethod::ADJ_LIST); // Value 1
			ImGui::SameLine();
			ImGui::RadioButton("Edge List", (int*)&graphInitOption, (int)GraphReader::GraphInitMethod::EDGE_LIST); // Value 2
			break;
		default:
			break;
		}

		// Change ItemSpacing temporarily
		ImVec2 originalItemSpacing = stylePtr->ItemSpacing;
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, originalItemSpacing.y));
		ImGui::Text("(Please enter your data in file ");
		ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 0.f, 1.f));
		ImGui::Text("\"data/%s\"", dataFileName.c_str());
		ImGui::PopStyleColor();
		ImGui::SameLine();
		ImGui::Text(" before confirmation.)");
		ImGui::PopStyleVar();
	}
	ImGui::EndGroup();


	ImGui::Dummy(ImVec2(20, 20));
	sf::Vector2u btnSize = {120, 40};
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + Im_gui_window_size.x/2.f - btnSize.x/2.f);

	// Confirm button
	ImGui::BeginDisabled(dataInitOption == DATA_INIT_CUSTOM && invalidDataCustom);
	if (ImGui::Button("Confirm", sf::Vector2f(btnSize))) {
		std::cout << DSVectors[current_DS_item].c_str() <<" "<<  dataInitOption << std::endl; // DEBUG

		// Change program mode
		///// --- MUST FINISH ALL 6 DATA STRUCTURES --- /////
		switch (chosenDSType) {
		case DSType::SINGLY_LINKED_LIST:
			invalidDataFromFile = !initSLL(dataInitOption);
			if (!invalidDataFromFile) {
				programState = ProgramState::VIS_SLL_SCREEN;
			}
			break;
		case DSType::HASH_TABLE:
			invalidDataFromFile = !initHashTable(dataInitOption);
			if (!invalidDataFromFile) {
				programState = ProgramState::VIS_HASH_SCREEN;
			}
			break;
		case DSType::AVL_TREE:
			invalidDataFromFile = !initAVL(dataInitOption);
			if (!invalidDataFromFile) {
				programState = ProgramState::VIS_AVL_SCREEN;
			}
			break;
		case DSType::TRIE_TREE:
			invalidDataFromFile = !initTrie(dataInitOption);
			if (!invalidDataFromFile) {
				programState = ProgramState::VIS_TRIE_SCREEN;
			}
			break;
		case DSType::MST_PRIM_GRAPH:
			invalidDataFromFile = !initGraph(dataInitOption, graphInitOption, customDataMSTPrimBuf, GRAPH_DATA_FILEPATH, graph_dataFile);
			if (!invalidDataFromFile) {
				programState = ProgramState::VIS_MST_PRIM_SCREEN;
			}
			break;
		case DSType::DIJKSTRA_GRAPH:
			invalidDataFromFile = !initGraph(dataInitOption, graphInitOption, customDataDijkstraBuf, GRAPH_DATA_FILEPATH, graph_dataFile);
			if (!invalidDataFromFile) {
				programState = ProgramState::VIS_DIJKSTRA_SCREEN;
			}
			break;
		default:
			break;
		}
	}
	ImGui::EndDisabled();

	// Print error message
	if (dataInitOption == DATA_INIT_FROM_FILE && invalidDataFromFile) {
		ImGui::Text("Your data is invalid. Check your .txt file and try again.");
	}

	ImGui::End();
}



void Program::finishChooseDSMenuScreen() {

}

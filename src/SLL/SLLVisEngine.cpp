#include "SLL/SLLVisEngine.h"





SLLVisEngine::SLLVisEngine(sf::RenderWindow& window, sf::Font& font)
	: window(window), font(font)
	, originPos(originPosDisplacement - sf::Vector2f(window.getSize()) / 2.f)
{
	// Initialize linked list (ONLY FOR TESTING)
	pHead = new SLLNode{36, nullptr};
	pHead->pNext = new SLLNode{67, nullptr};
	pHead->pNext->pNext = new SLLNode{18, nullptr};
	pHead->pNext->pNext->pNext = new SLLNode{-1992, nullptr};
	// pSearch = pHead->pNext;
	size = 4;
}

SLLVisEngine::~SLLVisEngine() {
	clear();
}


void SLLVisEngine::increaseTime() {
	time += dt; // (ONLY FOR TESTING, FOR NOW)
}
void SLLVisEngine::decreaseTime() {
	time -= dt; // (ONLY FOR TESTING, FOR NOW)
}
void SLLVisEngine::prevStep() {
	targetTime = time - 1;
	targetTime = floor(targetTime);
	targetTime = std::max(targetTime, 0.f);
}
void SLLVisEngine::nextStep() {
	targetTime = time + 1;
	targetTime = floor(targetTime);
	targetTime = std::max(targetTime, 0.f);
}


void SLLVisEngine::resetParams() {
	visCur = nullptr; // cur in visualization (not in code)
	visCurIndex = 0; // cur index in visualization (not in code)

	pSearch = nullptr;
	pInsert = nullptr;
	pCurCreated = false;

	animInProgress = false;

	animStepIndex = 0; // first step
	oldAnimStepIndex = 0; // first step
	time = 0;
}



void SLLVisEngine::addNodeDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList) {
	// Draw pHead
	auto headBox = std::make_unique<sf::RectangleShape>(nodeValueRectSize);
	headBox->setFillColor(sf::Color::Transparent);
	headBox->setOutlineColor(sf::Color::Black);
	headBox->setOutlineThickness(2.f);
	headBox->setPosition(originPos
		+ sf::Vector2f(headPosDisplacement)
	);
	drawableList.push_back(std::move(headBox));

	// Display nodes: Iterate through linked list and draw nodes
	int index = 0;
	SLLNode* cur = pHead;
	while (cur) {
		auto bigNodeBox = std::make_unique<sf::RectangleShape>(nodeRectSize);
		bigNodeBox->setFillColor(sf::Color::Transparent);
		bigNodeBox->setOutlineColor(
			// (cur == visCur && visCur == pSearch && time >= 1) ? sf::Color::Green : sf::Color::Black
			(cur == pSearch) ? sf::Color::Green : sf::Color::Black
		);
		bigNodeBox->setOutlineThickness(2.f);
		bigNodeBox->setPosition(originPos 
			+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
		);
		
		auto smallNodeBox = std::make_unique<sf::RectangleShape>(nodeValueRectSize);
		smallNodeBox->setFillColor(sf::Color::Transparent);
		smallNodeBox->setOutlineColor(
			// (cur == visCur && visCur == pSearch && time >= 1) ? sf::Color::Green : sf::Color::Black
			(cur == pSearch) ? sf::Color::Green : sf::Color::Black
		);
		smallNodeBox->setOutlineThickness(2.f);
		smallNodeBox->setPosition(originPos 
			+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
		);

		auto valueText = std::make_unique<sf::Text>(font, std::to_string(cur->val), valueFontSize);
		sf::FloatRect localBounds = valueText->getLocalBounds();
		valueText->setOrigin({localBounds.position.x + localBounds.size.x / 2.f, localBounds.position.y + localBounds.size.y / 2.f});
		valueText->setFillColor(sf::Color::Black);
		valueText->setPosition(originPos 
			+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
			+ nodeValueRectSize / 2.f
		);

		auto linkLine = std::make_unique<sf::VertexArray>(sf::PrimitiveType::Lines, 2);
		(*linkLine)[0].position = originPos 
			+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
			+ sf::Vector2f(nodeRectSize.x, nodeRectSize.y/2);
		(*linkLine)[0].color    = sf::Color::Black;
		sf::Vector2f arrowHeadPos = originPos
			+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
			+ sf::Vector2f(nodeRectSize.x + linkArrowLength, nodeRectSize.y/2);
		(*linkLine)[1].position = arrowHeadPos;
		(*linkLine)[1].color    = sf::Color::Black;

		auto linkArrowHead = std::make_unique<sf::VertexArray>(sf::PrimitiveType::Triangles, 3);
		(*linkArrowHead)[0].position = arrowHeadPos;
		(*linkArrowHead)[0].color    = sf::Color::Black;
		(*linkArrowHead)[1].position = arrowHeadPos - sf::Vector2f(0.866f * arrowHeadLength, arrowHeadLength / 2.f);
		(*linkArrowHead)[1].color    = sf::Color::Black;
		(*linkArrowHead)[2].position = arrowHeadPos - sf::Vector2f(0.866f * arrowHeadLength, -arrowHeadLength / 2.f);
		(*linkArrowHead)[2].color    = sf::Color::Black;

		drawableList.push_back(std::move(bigNodeBox));
		drawableList.push_back(std::move(smallNodeBox));
		drawableList.push_back(std::move(valueText));
		drawableList.push_back(std::move(linkLine));
		drawableList.push_back(std::move(linkArrowHead));

		cur = cur->pNext;
		index++;
	}
	// Draw null node
	auto bigNullBox = std::make_unique<sf::RectangleShape>(nodeRectSize);
	bigNullBox->setFillColor(sf::Color::Transparent);
	bigNullBox->setOutlineColor(sf::Color::Black);
	bigNullBox->setOutlineThickness(2.f);
	bigNullBox->setPosition(originPos 
		+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
	);

	auto nullDiagonal = std::make_unique<sf::VertexArray>(sf::PrimitiveType::Lines, 2);
	(*nullDiagonal)[0].position = originPos 
		+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
		+ sf::Vector2f(nodeRectSize.x, 0.f);
	(*nullDiagonal)[0].color    = sf::Color::Black;
	(*nullDiagonal)[1].position = originPos 
		+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
		+ sf::Vector2f(0.f, nodeRectSize.y);
	(*nullDiagonal)[1].color    = sf::Color::Black;

	auto nullText = std::make_unique<sf::Text>(font, "NULL", valueFontSize);
	sf::FloatRect localBounds = nullText->getLocalBounds();
	nullText->setOrigin({localBounds.position.x + localBounds.size.x / 2.f, localBounds.position.y + localBounds.size.y / 2.f});
	nullText->setFillColor(sf::Color::Black);
	nullText->setPosition(originPos 
		+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
		+ nodeRectSize / 2.f
	);

	drawableList.push_back(std::move(bigNullBox));
	drawableList.push_back(std::move(nullDiagonal));
	drawableList.push_back(std::move(nullText));
}



void SLLVisEngine::addNodeDrawablesInsert(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, SLLAnimStep eventSLL) {
	// Draw pHead
	auto headBox = std::make_unique<sf::RectangleShape>(nodeValueRectSize);
	headBox->setFillColor(sf::Color::Transparent);
	headBox->setOutlineColor(sf::Color::Black);
	headBox->setOutlineThickness(2.f);
	headBox->setPosition(originPos
		+ sf::Vector2f(headPosDisplacement)
	);
	drawableList.push_back(std::move(headBox));

	// Display nodes: Iterate through linked list and draw nodes
	int index = 0;
	SLLNode* cur = pHead;
	while (cur) {
		if (// eventSLL.type != SLLAnimType::LINK_NEW_NODE_TO_NEXT && 
			// eventSLL.type != SLLAnimType::LINK_PREV_TO_NEW_NODE && 
			// eventSLL.type != SLLAnimType::LINK_HEAD_TO_NEW_NODE && 
			eventSLL.type != SLLAnimType::MOVE_NODES_INSERT_K   &&
			eventSLL.type != SLLAnimType::MOVE_NODES_INSERT_BEG) {
			if (cur == pInsert) {
				cur = cur->pNext;
				continue;
			}
		}

		auto bigNodeBox = std::make_unique<sf::RectangleShape>(nodeRectSize);
		bigNodeBox->setFillColor(sf::Color::Transparent);
		bigNodeBox->setOutlineColor(
			// (cur == visCur && visCur == pSearch && time >= 1) ? sf::Color::Green : sf::Color::Black
			(cur == pSearch) ? sf::Color::Green : sf::Color::Black
		);
		bigNodeBox->setOutlineThickness(2.f);
		bigNodeBox->setPosition(originPos 
			+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
		);
		
		auto smallNodeBox = std::make_unique<sf::RectangleShape>(nodeValueRectSize);
		smallNodeBox->setFillColor(sf::Color::Transparent);
		smallNodeBox->setOutlineColor(
			// (cur == visCur && visCur == pSearch && time >= 1) ? sf::Color::Green : sf::Color::Black
			(cur == pSearch) ? sf::Color::Green : sf::Color::Black
		);
		smallNodeBox->setOutlineThickness(2.f);
		smallNodeBox->setPosition(originPos 
			+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
		);

		auto valueText = std::make_unique<sf::Text>(font, std::to_string(cur->val), valueFontSize);
		sf::FloatRect localBounds = valueText->getLocalBounds();
		valueText->setOrigin({localBounds.position.x + localBounds.size.x / 2.f, localBounds.position.y + localBounds.size.y / 2.f});
		valueText->setFillColor(sf::Color::Black);
		valueText->setPosition(originPos 
			+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
			+ nodeValueRectSize / 2.f
		);

		auto linkLine = std::make_unique<sf::VertexArray>(sf::PrimitiveType::Lines, 2);
		(*linkLine)[0].position = originPos 
			+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
			+ sf::Vector2f(nodeRectSize.x, nodeRectSize.y/2);
		(*linkLine)[0].color    = sf::Color::Black;
		sf::Vector2f arrowHeadPos = originPos
			+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
			+ sf::Vector2f(nodeRectSize.x + linkArrowLength, nodeRectSize.y/2);
		(*linkLine)[1].position = arrowHeadPos;
		(*linkLine)[1].color    = sf::Color::Black;

		auto linkArrowHead = std::make_unique<sf::VertexArray>(sf::PrimitiveType::Triangles, 3);
		(*linkArrowHead)[0].position = arrowHeadPos;
		(*linkArrowHead)[0].color    = sf::Color::Black;
		(*linkArrowHead)[1].position = arrowHeadPos - sf::Vector2f(0.866f * arrowHeadLength, arrowHeadLength / 2.f);
		(*linkArrowHead)[1].color    = sf::Color::Black;
		(*linkArrowHead)[2].position = arrowHeadPos - sf::Vector2f(0.866f * arrowHeadLength, -arrowHeadLength / 2.f);
		(*linkArrowHead)[2].color    = sf::Color::Black;

		drawableList.push_back(std::move(bigNodeBox));
		drawableList.push_back(std::move(smallNodeBox));
		drawableList.push_back(std::move(valueText));
		drawableList.push_back(std::move(linkLine));
		drawableList.push_back(std::move(linkArrowHead));

		cur = cur->pNext;
		index++;
	}
	// Draw null node
	auto bigNullBox = std::make_unique<sf::RectangleShape>(nodeRectSize);
	bigNullBox->setFillColor(sf::Color::Transparent);
	bigNullBox->setOutlineColor(sf::Color::Black);
	bigNullBox->setOutlineThickness(2.f);
	bigNullBox->setPosition(originPos 
		+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
	);

	auto nullDiagonal = std::make_unique<sf::VertexArray>(sf::PrimitiveType::Lines, 2);
	(*nullDiagonal)[0].position = originPos 
		+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
		+ sf::Vector2f(nodeRectSize.x, 0.f);
	(*nullDiagonal)[0].color    = sf::Color::Black;
	(*nullDiagonal)[1].position = originPos 
		+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
		+ sf::Vector2f(0.f, nodeRectSize.y);
	(*nullDiagonal)[1].color    = sf::Color::Black;

	auto nullText = std::make_unique<sf::Text>(font, "NULL", valueFontSize);
	sf::FloatRect localBounds = nullText->getLocalBounds();
	nullText->setOrigin({localBounds.position.x + localBounds.size.x / 2.f, localBounds.position.y + localBounds.size.y / 2.f});
	nullText->setFillColor(sf::Color::Black);
	nullText->setPosition(originPos 
		+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
		+ nodeRectSize / 2.f
	);

	drawableList.push_back(std::move(bigNullBox));
	drawableList.push_back(std::move(nullDiagonal));
	drawableList.push_back(std::move(nullText));

	// -- DRAW INSERTED NODE --
	if (pInsert != nullptr) {
		auto bigInsertBox = std::make_unique<sf::RectangleShape>(nodeRectSize);
		bigInsertBox->setFillColor(sf::Color::Transparent);
		bigInsertBox->setOutlineColor(sf::Color::Black);
		bigInsertBox->setOutlineThickness(2.f);
		bigInsertBox->setPosition(originPos 
			+ static_cast<float>(idxInsert) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
			+ sf::Vector2f(0.f, nodeLayerSpacing)
		);

		auto smallInsertBox = std::make_unique<sf::RectangleShape>(nodeValueRectSize);
		smallInsertBox->setFillColor(sf::Color::Transparent);
		smallInsertBox->setOutlineColor(sf::Color::Black);
		smallInsertBox->setOutlineThickness(2.f);
		smallInsertBox->setPosition(originPos 
			+ static_cast<float>(idxInsert) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
			+ sf::Vector2f(0.f, nodeLayerSpacing)
		);

		auto valueTextInsert = std::make_unique<sf::Text>(font, std::to_string(pInsert->val), valueFontSize);
		sf::FloatRect localBounds = valueTextInsert->getLocalBounds();
		valueTextInsert->setOrigin({localBounds.position.x + localBounds.size.x / 2.f, localBounds.position.y + localBounds.size.y / 2.f});
		valueTextInsert->setFillColor(sf::Color::Black);
		valueTextInsert->setPosition(originPos 
			+ static_cast<float>(idxInsert) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
			+ nodeValueRectSize / 2.f
			+ sf::Vector2f(0.f, nodeLayerSpacing)
		);

		if (eventSLL.type == SLLAnimType::LINK_NEW_NODE_TO_NEXT || 
			eventSLL.type == SLLAnimType::LINK_HEAD_TO_NEW_NODE || 
			eventSLL.type == SLLAnimType::LINK_PREV_TO_NEW_NODE) {
			if (eventSLL.insertLinkNext) {
				auto linkLine = std::make_unique<sf::VertexArray>(sf::PrimitiveType::Lines, 2);
				(*linkLine)[0].position = originPos 
					+ static_cast<float>(idxInsert) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
					+ sf::Vector2f(nodeRectSize.x, nodeRectSize.y/2)
					+ sf::Vector2f(0, nodeLayerSpacing);
				(*linkLine)[0].color    = sf::Color::Black;
				sf::Vector2f arrowHeadPos = originPos
					+ static_cast<float>(idxInsert) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
					+ sf::Vector2f(nodeRectSize.x + linkArrowLength, nodeRectSize.y/2)
					+ sf::Vector2f(- linkArrowLength - nodeRectSize.x/2, nodeRectSize.y/2);
				(*linkLine)[1].position = arrowHeadPos;
				(*linkLine)[1].color    = sf::Color::Black;

				drawableList.push_back(std::move(linkLine));
			}
			if (eventSLL.insertLinkPrev) {
				auto linkLine = std::make_unique<sf::VertexArray>(sf::PrimitiveType::Lines, 2);
				(*linkLine)[0].position = originPos 
					+ static_cast<float>(idxInsert-1) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
					+ sf::Vector2f(nodeRectSize.x, nodeRectSize.y/2);
				(*linkLine)[0].color    = sf::Color::Black;
				sf::Vector2f arrowHeadPos = originPos
					+ static_cast<float>(idxInsert-1) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
					+ sf::Vector2f(nodeRectSize.x + linkArrowLength, nodeRectSize.y/2);
				(*linkLine)[1].position = arrowHeadPos + sf::Vector2f(0, nodeLayerSpacing);
				(*linkLine)[1].color    = sf::Color::Black;

				drawableList.push_back(std::move(linkLine));
			}
		}

		// if (eventSLL.type == SLLAnimType::LINK_NEW_NODE_TO_NEXT) {
		// 
		// }

		drawableList.push_back(std::move(bigInsertBox));
		drawableList.push_back(std::move(smallInsertBox));
		drawableList.push_back(std::move(valueTextInsert));
		// drawableList.push_back(std::move(linkLine));
		// drawableList.push_back(std::move(linkArrowHead));
	}
}



void SLLVisEngine::createDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList) {
	drawableList.clear();


	// If STILL mode, stop here
	if (eventList.size() <= 1) {
		// Display nodes: Iterate through linked list and draw nodes
		addNodeDrawables(drawableList);
		return;
	}


	// change visCur and visCurIndex
	animStepIndex = std::min(static_cast<int>(floor(time)), static_cast<int>(eventList.size()) - 1);
	time = std::min(std::max(time, 0.f), static_cast<float>(eventList.size()));
	SLLAnimStep eventSLL = eventList[animStepIndex];
	// Set parameters
	pSearch = eventSLL.pSearch; // Set pSearch in the event
	animInProgress = (time != static_cast<float>(eventList.size()));

	if (animStepIndex > oldAnimStepIndex) {
		if (eventList[oldAnimStepIndex].type == SLLAnimType::MOVE_CUR_FORWARD) {
			visCurIndex++;
			visCur = visCur->pNext;
		}
		oldAnimStepIndex = animStepIndex;
	}


	// INSERT MODE
	if (visMode == SLLVisMode::INSERT_BEG || visMode == SLLVisMode::INSERT_END || visMode == SLLVisMode::INSERT_K) {
		// Display nodes: Iterate through linked list and draw nodes
		pInsert = ithNode(eventSLL.idxInsert);
		idxInsert = eventSLL.idxInsert;
		addNodeDrawablesInsert(drawableList, eventSLL);
	} else {
		addNodeDrawables(drawableList);
	}


	// Display description for algorithm visualization
	auto descriptionText = std::make_unique<sf::Text>(font, eventSLL.text, descriptionFontSize);
	descriptionText->setFillColor(sf::Color::Black);
	descriptionText->setPosition(originPos - originPosDisplacement + descriptionTextPos);

	// Display animation step
	auto curBox = std::make_unique<sf::RectangleShape>(nodeValueRectSize);
	switch (eventSLL.type) {
	case SLLAnimType::NONE:
		curBox->setPosition(originPos
			+ sf::Vector2f(0, 100)
			// + static_cast<float>(visCurIndex) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
			+ static_cast<float>(eventSLL.curIndex) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
		);
		break;
	case SLLAnimType::CREATE_CUR:
		visCur = pHead;
		visCurIndex = 0;
		
		curBox->setPosition(originPos
			+ sf::Vector2f(0, 100)
			+ static_cast<float>(eventSLL.curIndex) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
		);
		break;
	case SLLAnimType::MOVE_CUR_FORWARD:
		curBox->setPosition(originPos
			+ sf::Vector2f(0, 100)
			+ static_cast<float>(eventSLL.curIndex) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
			+ lerp(sf::Vector2f(0, 0), sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f), time - floor(time))
		);
		break;
	default:
		curBox->setPosition(originPos
			+ sf::Vector2f(0, 100)
			+ static_cast<float>(eventSLL.curIndex) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
		);
		break;
	}
	curBox->setFillColor(sf::Color::Transparent);
	curBox->setOutlineColor(sf::Color::Black);
	curBox->setOutlineThickness(2.f);

	drawableList.push_back(std::move(descriptionText));
	drawableList.push_back(std::move(curBox));

	std::cout << drawableList.size() << ' ' << time << " init done\n";
}



void SLLVisEngine::displayDrawables(std::unique_ptr<sfLayout>& sfmlLayout) {
	sfmlLayout->displayAll();
}





sf::Vector2f SLLVisEngine::lerp(sf::Vector2f v1, sf::Vector2f v2, float k) const {
	return v1 + (v2 - v1) * k;
}

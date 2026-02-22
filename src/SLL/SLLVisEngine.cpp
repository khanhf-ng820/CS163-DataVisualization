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

	insertLinkPrev = false;
	insertLinkNext = false;
	oldUpdateVal = -1;

	oldRemoveVal = false;
	idxRemove = -1;

	animInProgress = false;

	animStepIndex = 0; // first step
	oldAnimStepIndex = 0; // first step
	time = 0;
}



// --- NORMAL | SEARCH | UPDATE MODE ---
void SLLVisEngine::addNodeDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, SLLAnimStep eventSLL) {
	// Draw pHead
	auto headBox = std::make_unique<sf::RectangleShape>(nodeValueRectSize);
	headBox->setFillColor(sf::Color::Transparent);
	headBox->setOutlineColor(sf::Color::Black);
	headBox->setOutlineThickness(2.f);
	headBox->setPosition(originPos + headPosDisplacement);
	auto pHeadText = std::make_unique<sf::Text>(font, "pHead", valueFontSize);
	pHeadText->setFillColor(sf::Color::Black);
	pHeadText->setPosition(originPos + headPosDisplacement);
	drawableList.push_back(std::move(headBox));
	drawableList.push_back(std::move(pHeadText));

	drawArrow(
		drawableList,
		originPos + headPosDisplacement + sf::Vector2f(nodeValueRectSize.x, nodeValueRectSize.y/2),
		originPos + headPosDisplacement + sf::Vector2f(nodeValueRectSize.x + linkArrowLength, nodeValueRectSize.y/2)
	);

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

		// Text inside node (usually value of node)
		std::string valueTextStr = (visMode == SLLVisMode::UPDATE && eventSLL.type != SLLAnimType::UPDATE_CUR_VAL)
								 ? std::to_string(oldUpdateVal) : std::to_string(cur->val);
		auto valueText = std::make_unique<sf::Text>(font, std::to_string(cur->val), valueFontSize);
		sf::FloatRect localBounds = valueText->getLocalBounds();
		valueText->setOrigin({localBounds.position.x + localBounds.size.x / 2.f, localBounds.position.y + localBounds.size.y / 2.f});
		valueText->setFillColor(sf::Color::Black);
		valueText->setPosition(originPos 
			+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
			+ nodeValueRectSize / 2.f
		);

		sf::Vector2f arrowHeadPos = originPos
			+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
			+ sf::Vector2f(nodeRectSize.x + linkArrowLength, nodeRectSize.y/2);
		drawArrow(drawableList,
			originPos 
			+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
			+ sf::Vector2f(nodeRectSize.x, nodeRectSize.y/2),
			arrowHeadPos
		);

		drawableList.push_back(std::move(bigNodeBox));
		drawableList.push_back(std::move(smallNodeBox));
		drawableList.push_back(std::move(valueText));
		// drawableList.push_back(std::move(linkLine));
		// drawableList.push_back(std::move(linkArrowHead));

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



// --- INSERT MODE ONLY ---
void SLLVisEngine::addNodeDrawablesInsert(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, SLLAnimStep eventSLL) {
	// Draw pHead
	auto headBox = std::make_unique<sf::RectangleShape>(nodeValueRectSize);
	headBox->setFillColor(sf::Color::Transparent);
	headBox->setOutlineColor(sf::Color::Black);
	headBox->setOutlineThickness(2.f);
	headBox->setPosition(originPos + headPosDisplacement);
	auto pHeadText = std::make_unique<sf::Text>(font, "pHead", valueFontSize);
	pHeadText->setFillColor(sf::Color::Black);
	pHeadText->setPosition(originPos + headPosDisplacement);

	drawableList.push_back(std::move(headBox));
	drawableList.push_back(std::move(pHeadText));
	// In LINK_HEAD_TO_NEW_NODE step and after:
	if (!(eventSLL.type == SLLAnimType::LINK_HEAD_TO_NEW_NODE || eventSLL.type == SLLAnimType::MOVE_NODES_INSERT_BEG)) {
		drawArrow(
			drawableList,
			originPos + headPosDisplacement + sf::Vector2f(nodeValueRectSize.x, nodeValueRectSize.y/2),
			originPos + headPosDisplacement + sf::Vector2f(nodeValueRectSize.x + linkArrowLength, nodeValueRectSize.y/2)
		);
	} else if (eventSLL.type == SLLAnimType::LINK_HEAD_TO_NEW_NODE) {
		// Link pHead to -> new node instead
		drawArrow(
			drawableList,
			originPos + headPosDisplacement + sf::Vector2f(nodeValueRectSize.x, nodeValueRectSize.y/2),
			originPos + headPosDisplacement + sf::Vector2f(nodeValueRectSize.x + linkArrowLength, nodeValueRectSize.y/2)
			+ sf::Vector2f(0, nodeLayerSpacing)
		);
	} else {
		// For INSERT mode
		drawArrow(
			drawableList,
			originPos + headPosDisplacement + sf::Vector2f(nodeValueRectSize.x, nodeValueRectSize.y/2),
			originPos + headPosDisplacement + sf::Vector2f(nodeValueRectSize.x + linkArrowLength, nodeValueRectSize.y/2)
			+ sf::Vector2f(0, nodeLayerSpacing)
			// For INSERT mode
			+ lerp(sf::Vector2f(), sf::Vector2f(0.f, - nodeLayerSpacing), fract(time))
		);
	}

	// Display nodes: Iterate through linked list and draw nodes
	int index = 0;
	SLLNode* cur = pHead;
	while (cur) {
		if (// eventSLL.type != SLLAnimType::LINK_NEW_NODE_TO_NEXT && 
			// eventSLL.type != SLLAnimType::LINK_PREV_TO_NEW_NODE && 
			// eventSLL.type != SLLAnimType::LINK_HEAD_TO_NEW_NODE && 
			true || // *** RESOLVE THIS LATER ***
			(eventSLL.type != SLLAnimType::MOVE_NODES_INSERT_K &&
			eventSLL.type != SLLAnimType::MOVE_NODES_INSERT_BEG)) {
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
			// for INSERT mode
			+ ((eventSLL.type == SLLAnimType::MOVE_NODES_INSERT_K || eventSLL.type == SLLAnimType::MOVE_NODES_INSERT_BEG) && index >= idxInsert ? lerp(sf::Vector2f(), sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f), fract(time)) : sf::Vector2f())
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
			// for INSERT mode
			+ ((eventSLL.type == SLLAnimType::MOVE_NODES_INSERT_K || eventSLL.type == SLLAnimType::MOVE_NODES_INSERT_BEG) && index >= idxInsert ? lerp(sf::Vector2f(), sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f), fract(time)) : sf::Vector2f())
		);

		auto valueText = std::make_unique<sf::Text>(font, std::to_string(cur->val), valueFontSize);
		sf::FloatRect localBounds = valueText->getLocalBounds();
		valueText->setOrigin({localBounds.position.x + localBounds.size.x / 2.f, localBounds.position.y + localBounds.size.y / 2.f});
		valueText->setFillColor(sf::Color::Black);
		valueText->setPosition(originPos 
			+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
			+ nodeValueRectSize / 2.f
			// for INSERT mode
			+ ((eventSLL.type == SLLAnimType::MOVE_NODES_INSERT_K || eventSLL.type == SLLAnimType::MOVE_NODES_INSERT_BEG) && index >= idxInsert ? lerp(sf::Vector2f(), sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f), fract(time)) : sf::Vector2f())
		);

		sf::Vector2f arrowHeadPos = originPos
			+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
			+ sf::Vector2f(nodeRectSize.x + linkArrowLength, nodeRectSize.y/2)
			// for INSERT mode
			+ ((eventSLL.type == SLLAnimType::MOVE_NODES_INSERT_K || eventSLL.type == SLLAnimType::MOVE_NODES_INSERT_BEG) && index >= idxInsert ? lerp(sf::Vector2f(), sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f), fract(time)) : sf::Vector2f());


		drawableList.push_back(std::move(bigNodeBox));
		drawableList.push_back(std::move(smallNodeBox));
		drawableList.push_back(std::move(valueText));
		// In LINK_PREV_TO_NEW_NODE step and after: Don't draw that one link
		if (!(eventSLL.type == SLLAnimType::LINK_PREV_TO_NEW_NODE || eventSLL.type == SLLAnimType::MOVE_NODES_INSERT_K || eventSLL.type == SLLAnimType::MOVE_NODES_INSERT_BEG)) {
			// drawableList.push_back(std::move(linkLine));
			// drawableList.push_back(std::move(linkArrowHead));
			drawArrow(drawableList,
				originPos 
				+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
				+ sf::Vector2f(nodeRectSize.x, nodeRectSize.y/2)
				// for INSERT mode
				+ ((eventSLL.type == SLLAnimType::MOVE_NODES_INSERT_K || eventSLL.type == SLLAnimType::MOVE_NODES_INSERT_BEG) && index >= idxInsert ? lerp(sf::Vector2f(), sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f), fract(time)) : sf::Vector2f()),
				arrowHeadPos
			);
		} else {
			if (index != idxInsert-1) {
				// drawableList.push_back(std::move(linkLine));
				// drawableList.push_back(std::move(linkArrowHead));
				drawArrow(drawableList,
					originPos 
					+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
					+ sf::Vector2f(nodeRectSize.x, nodeRectSize.y/2)
					// for INSERT mode
					+ ((eventSLL.type == SLLAnimType::MOVE_NODES_INSERT_K || eventSLL.type == SLLAnimType::MOVE_NODES_INSERT_BEG) && index >= idxInsert ? lerp(sf::Vector2f(), sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f), fract(time)) : sf::Vector2f()),
					arrowHeadPos
				);
			}
		}

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
		// for INSERT mode
		+ ((eventSLL.type == SLLAnimType::MOVE_NODES_INSERT_K || eventSLL.type == SLLAnimType::MOVE_NODES_INSERT_BEG) ? lerp(sf::Vector2f(), sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f), fract(time)) : sf::Vector2f())
	);

	auto nullDiagonal = std::make_unique<sf::VertexArray>(sf::PrimitiveType::Lines, 2);
	(*nullDiagonal)[0].position = originPos 
		+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
		+ sf::Vector2f(nodeRectSize.x, 0.f)
		// for INSERT mode
		+ ((eventSLL.type == SLLAnimType::MOVE_NODES_INSERT_K || eventSLL.type == SLLAnimType::MOVE_NODES_INSERT_BEG) ? lerp(sf::Vector2f(), sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f), fract(time)) : sf::Vector2f());
	(*nullDiagonal)[0].color    = sf::Color::Black;
	(*nullDiagonal)[1].position = originPos 
		+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
		+ sf::Vector2f(0.f, nodeRectSize.y)
		// for INSERT mode
		+ ((eventSLL.type == SLLAnimType::MOVE_NODES_INSERT_K || eventSLL.type == SLLAnimType::MOVE_NODES_INSERT_BEG) ? lerp(sf::Vector2f(), sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f), fract(time)) : sf::Vector2f());
	(*nullDiagonal)[1].color    = sf::Color::Black;

	auto nullText = std::make_unique<sf::Text>(font, "NULL", valueFontSize);
	sf::FloatRect localBounds = nullText->getLocalBounds();
	nullText->setOrigin({localBounds.position.x + localBounds.size.x / 2.f, localBounds.position.y + localBounds.size.y / 2.f});
	nullText->setFillColor(sf::Color::Black);
	nullText->setPosition(originPos 
		+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
		+ nodeRectSize / 2.f
		// for INSERT mode
		+ ((eventSLL.type == SLLAnimType::MOVE_NODES_INSERT_K || eventSLL.type == SLLAnimType::MOVE_NODES_INSERT_BEG) ? lerp(sf::Vector2f(), sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f), fract(time)) : sf::Vector2f())
	);

	drawableList.push_back(std::move(bigNullBox));
	drawableList.push_back(std::move(nullDiagonal));
	drawableList.push_back(std::move(nullText));

	// -- DRAW INSERTED NODE --
	if (pInsert != nullptr && eventSLL.type != SLLAnimType::CREATE_CUR && eventSLL.type != SLLAnimType::MOVE_CUR_FORWARD) {
		auto bigInsertBox = std::make_unique<sf::RectangleShape>(nodeRectSize);
		bigInsertBox->setFillColor(sf::Color::Transparent);
		bigInsertBox->setOutlineColor(sf::Color::Black);
		bigInsertBox->setOutlineThickness(2.f);
		bigInsertBox->setPosition(originPos 
			+ static_cast<float>(idxInsert) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
			+ sf::Vector2f(0.f, nodeLayerSpacing)
			// for INSERT mode
			+ ((eventSLL.type == SLLAnimType::MOVE_NODES_INSERT_K || eventSLL.type == SLLAnimType::MOVE_NODES_INSERT_BEG) ? lerp(sf::Vector2f(), sf::Vector2f(0.f, - nodeLayerSpacing), fract(time)) : sf::Vector2f())
		);

		auto smallInsertBox = std::make_unique<sf::RectangleShape>(nodeValueRectSize);
		smallInsertBox->setFillColor(sf::Color::Transparent);
		smallInsertBox->setOutlineColor(sf::Color::Black);
		smallInsertBox->setOutlineThickness(2.f);
		smallInsertBox->setPosition(originPos 
			+ static_cast<float>(idxInsert) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
			+ sf::Vector2f(0.f, nodeLayerSpacing)
			// for INSERT mode
			+ ((eventSLL.type == SLLAnimType::MOVE_NODES_INSERT_K || eventSLL.type == SLLAnimType::MOVE_NODES_INSERT_BEG) ? lerp(sf::Vector2f(), sf::Vector2f(0.f, - nodeLayerSpacing), fract(time)) : sf::Vector2f())
		);

		auto valueTextInsert = std::make_unique<sf::Text>(font, std::to_string(pInsert->val), valueFontSize);
		sf::FloatRect localBounds = valueTextInsert->getLocalBounds();
		valueTextInsert->setOrigin({localBounds.position.x + localBounds.size.x / 2.f, localBounds.position.y + localBounds.size.y / 2.f});
		valueTextInsert->setFillColor(sf::Color::Black);
		valueTextInsert->setPosition(originPos 
			+ static_cast<float>(idxInsert) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
			+ nodeValueRectSize / 2.f
			+ sf::Vector2f(0.f, nodeLayerSpacing)
			// for INSERT mode
			+ ((eventSLL.type == SLLAnimType::MOVE_NODES_INSERT_K || eventSLL.type == SLLAnimType::MOVE_NODES_INSERT_BEG) ? lerp(sf::Vector2f(), sf::Vector2f(0.f, - nodeLayerSpacing), fract(time)) : sf::Vector2f())
		);

		if (eventSLL.type == SLLAnimType::LINK_NEW_NODE_TO_NEXT || 
			eventSLL.type == SLLAnimType::LINK_HEAD_TO_NEW_NODE || 
			eventSLL.type == SLLAnimType::LINK_PREV_TO_NEW_NODE) {
			if (eventSLL.insertLinkNext) {
				sf::Vector2f arrowHeadPos = originPos
					+ static_cast<float>(idxInsert) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
					+ sf::Vector2f(nodeRectSize.x + linkArrowLength, nodeRectSize.y/2)
					+ sf::Vector2f(- linkArrowLength - nodeRectSize.x/2, nodeRectSize.y/2);
				drawArrow(drawableList,
					originPos 
					+ static_cast<float>(idxInsert) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
					+ sf::Vector2f(nodeRectSize.x, nodeRectSize.y/2)
					+ sf::Vector2f(0, nodeLayerSpacing),
					arrowHeadPos
				);
			}
			if (eventSLL.insertLinkPrev) {
				sf::Vector2f arrowHeadPos = originPos
					+ static_cast<float>(idxInsert-1) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
					+ sf::Vector2f(nodeRectSize.x + linkArrowLength, nodeRectSize.y/2);
				drawArrow(drawableList,
					originPos 
					+ static_cast<float>(idxInsert-1) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
					+ sf::Vector2f(nodeRectSize.x, nodeRectSize.y/2),
					arrowHeadPos + sf::Vector2f(0, nodeLayerSpacing)
				);
			}
		} else if (eventSLL.type == SLLAnimType::MOVE_NODES_INSERT_K || eventSLL.type == SLLAnimType::MOVE_NODES_INSERT_BEG) {
			if (eventSLL.insertLinkNext) {
				drawArrow(drawableList,
					originPos 
					+ static_cast<float>(idxInsert) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
					+ sf::Vector2f(nodeRectSize.x, nodeRectSize.y/2)
					+ sf::Vector2f(0, nodeLayerSpacing)
					+ lerp(sf::Vector2f(), sf::Vector2f(0.f, - nodeLayerSpacing), fract(time)),
					originPos
					+ static_cast<float>(idxInsert) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
					+ sf::Vector2f(0, nodeRectSize.y/2)
					+ lerp(sf::Vector2f(), sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f), fract(time))
				);
			}
			if (eventSLL.insertLinkPrev) {
				sf::Vector2f arrowHeadPos = originPos
					+ static_cast<float>(idxInsert-1) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
					+ sf::Vector2f(nodeRectSize.x + linkArrowLength, nodeRectSize.y/2);
				drawArrow(drawableList,
					originPos 
					+ static_cast<float>(idxInsert-1) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
					+ sf::Vector2f(nodeRectSize.x, nodeRectSize.y/2),
					arrowHeadPos + sf::Vector2f(0, nodeLayerSpacing)
					+ lerp(sf::Vector2f(), sf::Vector2f(0.f, - nodeLayerSpacing), fract(time))
				);
			}
		}

		drawableList.push_back(std::move(bigInsertBox));
		drawableList.push_back(std::move(smallInsertBox));
		drawableList.push_back(std::move(valueTextInsert));
		// drawableList.push_back(std::move(linkLine));
		// drawableList.push_back(std::move(linkArrowHead));
	}
}



// --- REMOVE MODE ONLY ---
void SLLVisEngine::addNodeDrawablesRemove(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, SLLAnimStep eventSLL) {
	// Draw pHead
	auto headBox = std::make_unique<sf::RectangleShape>(nodeValueRectSize);
	headBox->setFillColor(sf::Color::Transparent);
	headBox->setOutlineColor(sf::Color::Black);
	headBox->setOutlineThickness(2.f);
	headBox->setPosition(originPos + headPosDisplacement);
	auto pHeadText = std::make_unique<sf::Text>(font, "pHead", valueFontSize);
	pHeadText->setFillColor(sf::Color::Black);
	pHeadText->setPosition(originPos + headPosDisplacement);

	drawableList.push_back(std::move(headBox));
	drawableList.push_back(std::move(pHeadText));
	// In CHANGE_LINK_OF_HEAD step and before:
	if (!(eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_BEG || eventSLL.type == SLLAnimType::CHANGE_LINK_OF_HEAD)) {
		drawArrow(
			drawableList,
			originPos + headPosDisplacement + sf::Vector2f(nodeValueRectSize.x, nodeValueRectSize.y/2),
			originPos + headPosDisplacement + sf::Vector2f(nodeValueRectSize.x + linkArrowLength, nodeValueRectSize.y/2)
		);
	} else if (eventSLL.type == SLLAnimType::CHANGE_LINK_OF_HEAD) {
		// Link pHead to the pNext of pNext
		drawArrow(
			drawableList,
			originPos + headPosDisplacement + sf::Vector2f(nodeValueRectSize.x, nodeValueRectSize.y/2),
			originPos + headPosDisplacement + sf::Vector2f(nodeValueRectSize.x + linkArrowLength, nodeValueRectSize.y/2)
			// + sf::Vector2f(0, nodeLayerSpacing)
		);
	} else {
		// For REMOVE mode
		drawArrow(
			drawableList,
			originPos + headPosDisplacement + sf::Vector2f(nodeValueRectSize.x, nodeValueRectSize.y/2),
			originPos + headPosDisplacement + sf::Vector2f(nodeValueRectSize.x + linkArrowLength, nodeValueRectSize.y/2)
			// For REMOVE mode
			+ lerp(sf::Vector2f(), sf::Vector2f(0.f, nodeLayerSpacing), fract(time))
		);
	}

	// Display nodes: Iterate through linked list and draw nodes
	int index = 0;
	SLLNode* cur = pHead;
	if (cur == nullptr && index == idxRemove) index++;
	while (cur) {
		if (index == idxRemove) {
			index++;
			continue;
		}

		auto bigNodeBox = std::make_unique<sf::RectangleShape>(nodeRectSize);
		bigNodeBox->setFillColor(sf::Color::Transparent);
		bigNodeBox->setOutlineColor(
			(cur == pSearch) ? sf::Color::Green : sf::Color::Black
		);
		bigNodeBox->setOutlineThickness(2.f);
		bigNodeBox->setPosition(originPos 
			+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
			// for REMOVE mode
			+ ((eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_K || eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_BEG) && index >= idxRemove ? -1.f * lerp(sf::Vector2f(), sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f), fract(time))
				: ((eventSLL.type == SLLAnimType::CHANGE_LINK_OF_CUR || eventSLL.type == SLLAnimType::CHANGE_LINK_OF_HEAD || eventSLL.type == SLLAnimType::REMOVE_NODE) && index >= idxRemove ? sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f) * -1.f : sf::Vector2f()))
		);
		
		auto smallNodeBox = std::make_unique<sf::RectangleShape>(nodeValueRectSize);
		smallNodeBox->setFillColor(sf::Color::Transparent);
		smallNodeBox->setOutlineColor(
			(cur == pSearch) ? sf::Color::Green : sf::Color::Black
		);
		smallNodeBox->setOutlineThickness(2.f);
		smallNodeBox->setPosition(originPos 
			+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
			// for REMOVE mode
			+ ((eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_K || eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_BEG) && index >= idxRemove ? -1.f * lerp(sf::Vector2f(), sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f), fract(time))
				: ((eventSLL.type == SLLAnimType::CHANGE_LINK_OF_CUR || eventSLL.type == SLLAnimType::CHANGE_LINK_OF_HEAD || eventSLL.type == SLLAnimType::REMOVE_NODE) && index >= idxRemove ? sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f) * -1.f : sf::Vector2f()))
		);

		auto valueText = std::make_unique<sf::Text>(font, std::to_string(cur->val), valueFontSize);
		sf::FloatRect localBounds = valueText->getLocalBounds();
		valueText->setOrigin({localBounds.position.x + localBounds.size.x / 2.f, localBounds.position.y + localBounds.size.y / 2.f});
		valueText->setFillColor(sf::Color::Black);
		valueText->setPosition(originPos 
			+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
			+ nodeValueRectSize / 2.f
			// for REMOVE mode
			+ ((eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_K || eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_BEG) && index >= idxRemove ? -1.f * lerp(sf::Vector2f(), sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f), fract(time))
				: ((eventSLL.type == SLLAnimType::CHANGE_LINK_OF_CUR || eventSLL.type == SLLAnimType::CHANGE_LINK_OF_HEAD || eventSLL.type == SLLAnimType::REMOVE_NODE) && index >= idxRemove ? sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f) * -1.f : sf::Vector2f()))
		);

		sf::Vector2f arrowHeadPos = originPos
			+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
			+ sf::Vector2f(nodeRectSize.x + linkArrowLength, nodeRectSize.y/2)
			// for REMOVE mode
			+ ((eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_K || eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_BEG) && index >= idxRemove ? -1.f * lerp(sf::Vector2f(), sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f), fract(time))
				: ((eventSLL.type == SLLAnimType::CHANGE_LINK_OF_CUR || eventSLL.type == SLLAnimType::CHANGE_LINK_OF_HEAD || eventSLL.type == SLLAnimType::REMOVE_NODE) && index >= idxRemove ? sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f) * -1.f : sf::Vector2f()));


		drawableList.push_back(std::move(bigNodeBox));
		drawableList.push_back(std::move(smallNodeBox));
		drawableList.push_back(std::move(valueText));

		if (!(eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_K || eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_BEG)) {
			drawArrow(drawableList,
				originPos 
				+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
				+ sf::Vector2f(nodeRectSize.x, nodeRectSize.y/2)
				// for REMOVE mode
				// + ((eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_K || eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_BEG) && index >= idxRemove ? -1.f * lerp(sf::Vector2f(), sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f), fract(time)) : sf::Vector2f()),
				+ ((eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_K || eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_BEG) && index >= idxRemove ? -1.f * lerp(sf::Vector2f(), sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f), fract(time))
					: ((eventSLL.type == SLLAnimType::CHANGE_LINK_OF_CUR || eventSLL.type == SLLAnimType::CHANGE_LINK_OF_HEAD || eventSLL.type == SLLAnimType::REMOVE_NODE) && index >= idxRemove ? sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f) * -1.f : sf::Vector2f())),
				arrowHeadPos
			);
		} else {
			if (index != idxRemove - 1)
				drawArrow(drawableList,
					originPos 
					+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
					+ sf::Vector2f(nodeRectSize.x, nodeRectSize.y/2)
					// for REMOVE mode
					// + ((eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_K || eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_BEG) && index >= idxRemove ? -1.f * lerp(sf::Vector2f(), sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f), fract(time)) : sf::Vector2f()),
					+ ((eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_K || eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_BEG) && index >= idxRemove ? -1.f * lerp(sf::Vector2f(), sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f), fract(time))
					: ((eventSLL.type == SLLAnimType::CHANGE_LINK_OF_CUR || eventSLL.type == SLLAnimType::CHANGE_LINK_OF_HEAD || eventSLL.type == SLLAnimType::REMOVE_NODE) && index >= idxRemove ? sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f) * -1.f : sf::Vector2f())),
					arrowHeadPos
				);
			else
				drawArrow(drawableList,
					originPos
					+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
					+ sf::Vector2f(nodeRectSize.x, nodeRectSize.y/2),
					arrowHeadPos
					// for REMOVE mode
					+ lerp(sf::Vector2f(), sf::Vector2f(0, nodeLayerSpacing), fract(time))
					// + lerp(sf::Vector2f(), sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f), fract(time))
				);
		}

		cur = cur->pNext;
		index++;

		if (cur == nullptr && index == idxRemove) index++;
	}
	// Draw null node
	auto bigNullBox = std::make_unique<sf::RectangleShape>(nodeRectSize);
	bigNullBox->setFillColor(sf::Color::Transparent);
	bigNullBox->setOutlineColor(sf::Color::Black);
	bigNullBox->setOutlineThickness(2.f);
	bigNullBox->setPosition(originPos 
		+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
		// for REMOVE mode
		// + ((eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_K || eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_BEG) ? -1.f * lerp(sf::Vector2f(), sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f), fract(time)) : sf::Vector2f())
		+ ((eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_K || eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_BEG) ? -1.f * lerp(sf::Vector2f(), sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f), fract(time))
		: ((eventSLL.type == SLLAnimType::CHANGE_LINK_OF_CUR || eventSLL.type == SLLAnimType::CHANGE_LINK_OF_HEAD || eventSLL.type == SLLAnimType::REMOVE_NODE) ? sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f) * -1.f : sf::Vector2f()))
	);

	auto nullDiagonal = std::make_unique<sf::VertexArray>(sf::PrimitiveType::Lines, 2);
	(*nullDiagonal)[0].position = originPos 
		+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
		+ sf::Vector2f(nodeRectSize.x, 0.f)
		// for REMOVE mode
		// + ((eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_K || eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_BEG) ? -1.f * lerp(sf::Vector2f(), sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f), fract(time)) : sf::Vector2f());
		+ ((eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_K || eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_BEG) ? -1.f * lerp(sf::Vector2f(), sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f), fract(time))
		: ((eventSLL.type == SLLAnimType::CHANGE_LINK_OF_CUR || eventSLL.type == SLLAnimType::CHANGE_LINK_OF_HEAD || eventSLL.type == SLLAnimType::REMOVE_NODE) ? sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f) * -1.f : sf::Vector2f()));
	(*nullDiagonal)[0].color    = sf::Color::Black;
	(*nullDiagonal)[1].position = originPos 
		+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
		+ sf::Vector2f(0.f, nodeRectSize.y)
		// for REMOVE mode
		// + ((eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_K || eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_BEG) ? -1.f * lerp(sf::Vector2f(), sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f), fract(time)) : sf::Vector2f());
		+ ((eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_K || eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_BEG) ? -1.f * lerp(sf::Vector2f(), sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f), fract(time))
		: ((eventSLL.type == SLLAnimType::CHANGE_LINK_OF_CUR || eventSLL.type == SLLAnimType::CHANGE_LINK_OF_HEAD || eventSLL.type == SLLAnimType::REMOVE_NODE) ? sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f) * -1.f : sf::Vector2f()));
	(*nullDiagonal)[1].color    = sf::Color::Black;

	auto nullText = std::make_unique<sf::Text>(font, "NULL", valueFontSize);
	sf::FloatRect localBounds = nullText->getLocalBounds();
	nullText->setOrigin({localBounds.position.x + localBounds.size.x / 2.f, localBounds.position.y + localBounds.size.y / 2.f});
	nullText->setFillColor(sf::Color::Black);
	nullText->setPosition(originPos 
		+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
		+ nodeRectSize / 2.f
		// for REMOVE mode
		// + ((eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_K || eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_BEG) ? -1.f * lerp(sf::Vector2f(), sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f), fract(time)) : sf::Vector2f())
		+ ((eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_K || eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_BEG) ? -1.f * lerp(sf::Vector2f(), sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f), fract(time))
		: ((eventSLL.type == SLLAnimType::CHANGE_LINK_OF_CUR || eventSLL.type == SLLAnimType::CHANGE_LINK_OF_HEAD || eventSLL.type == SLLAnimType::REMOVE_NODE) ? sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f) * -1.f : sf::Vector2f()))
	);

	drawableList.push_back(std::move(bigNullBox));
	drawableList.push_back(std::move(nullDiagonal));
	drawableList.push_back(std::move(nullText));

	// -- DRAW REMOVED NODE --
	if (eventSLL.type != SLLAnimType::REMOVE_NODE) {
		auto bigRemoveBox = std::make_unique<sf::RectangleShape>(nodeRectSize);
		bigRemoveBox->setFillColor(sf::Color::Transparent);
		bigRemoveBox->setOutlineColor(sf::Color::Black);
		bigRemoveBox->setOutlineThickness(2.f);
		bigRemoveBox->setPosition(originPos 
			+ static_cast<float>(idxRemove) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
			// + sf::Vector2f(0.f, nodeLayerSpacing)
			// for REMOVE mode
			+ ((eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_K || eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_BEG) ? lerp(sf::Vector2f(), sf::Vector2f(0.f, nodeLayerSpacing), fract(time)) :
				((eventSLL.type == SLLAnimType::CHANGE_LINK_OF_CUR || eventSLL.type == SLLAnimType::CHANGE_LINK_OF_HEAD || eventSLL.type == SLLAnimType::REMOVE_NODE) ? sf::Vector2f(0.f, nodeLayerSpacing) : sf::Vector2f()))
		);

		auto smallRemoveBox = std::make_unique<sf::RectangleShape>(nodeValueRectSize);
		smallRemoveBox->setFillColor(sf::Color::Transparent);
		smallRemoveBox->setOutlineColor(sf::Color::Black);
		smallRemoveBox->setOutlineThickness(2.f);
		smallRemoveBox->setPosition(originPos 
			+ static_cast<float>(idxRemove) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
			// + sf::Vector2f(0.f, nodeLayerSpacing)
			// for REMOVE mode
			+ ((eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_K || eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_BEG) ? lerp(sf::Vector2f(), sf::Vector2f(0.f, nodeLayerSpacing), fract(time)) :
				((eventSLL.type == SLLAnimType::CHANGE_LINK_OF_CUR || eventSLL.type == SLLAnimType::CHANGE_LINK_OF_HEAD || eventSLL.type == SLLAnimType::REMOVE_NODE) ? sf::Vector2f(0.f, nodeLayerSpacing) : sf::Vector2f()))
		);

		auto valueTextRemove = std::make_unique<sf::Text>(font, std::to_string(oldRemoveVal), valueFontSize);
		sf::FloatRect localBounds = valueTextRemove->getLocalBounds();
		valueTextRemove->setOrigin({localBounds.position.x + localBounds.size.x / 2.f, localBounds.position.y + localBounds.size.y / 2.f});
		valueTextRemove->setFillColor(sf::Color::Black);
		valueTextRemove->setPosition(originPos 
			+ static_cast<float>(idxRemove) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
			+ nodeValueRectSize / 2.f
			// for REMOVE mode
			+ ((eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_K || eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_BEG) ? lerp(sf::Vector2f(), sf::Vector2f(0.f, nodeLayerSpacing), fract(time)) :
				((eventSLL.type == SLLAnimType::CHANGE_LINK_OF_CUR || eventSLL.type == SLLAnimType::CHANGE_LINK_OF_HEAD || eventSLL.type == SLLAnimType::REMOVE_NODE) ? sf::Vector2f(0.f, nodeLayerSpacing) : sf::Vector2f()))
		);

		if (eventSLL.type == SLLAnimType::CREATE_CUR || eventSLL.type == SLLAnimType::MOVE_CUR_FORWARD) {
			drawArrow(drawableList,
				originPos 
				+ static_cast<float>(idxRemove) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
				+ sf::Vector2f(nodeRectSize.x, nodeRectSize.y/2),
				originPos
				+ static_cast<float>(idxRemove) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
				+ sf::Vector2f(nodeRectSize.x + linkArrowLength, nodeRectSize.y/2)
			);
		} else if (eventSLL.type == SLLAnimType::CHANGE_LINK_OF_CUR || eventSLL.type == SLLAnimType::CHANGE_LINK_OF_HEAD) {
			drawArrow(drawableList,
				originPos 
				+ static_cast<float>(idxRemove) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
				+ sf::Vector2f(nodeRectSize.x, nodeRectSize.y/2)
				+ sf::Vector2f(0, nodeLayerSpacing),
				originPos
				+ static_cast<float>(idxRemove) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
				+ sf::Vector2f(nodeRectSize.x + linkArrowLength, nodeRectSize.y/2)
				+ sf::Vector2f(- linkArrowLength - nodeRectSize.x/2, nodeRectSize.y/2)
			);
		} else if (eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_K || eventSLL.type == SLLAnimType::MOVE_NODES_REMOVE_BEG) {
			drawArrow(drawableList,
				originPos 
				+ static_cast<float>(idxRemove) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
				+ sf::Vector2f(nodeRectSize.x, nodeRectSize.y/2)
				+ sf::Vector2f(0, nodeLayerSpacing)
				+ lerp(sf::Vector2f(0.f, - nodeLayerSpacing), sf::Vector2f(), fract(time)),
				originPos
				+ static_cast<float>(idxRemove) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
				+ sf::Vector2f(0, nodeRectSize.y/2)
				+ lerp(sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f), sf::Vector2f(), fract(time))
			);
		}

		drawableList.push_back(std::move(bigRemoveBox));
		drawableList.push_back(std::move(smallRemoveBox));
		drawableList.push_back(std::move(valueTextRemove));
	}
}



void SLLVisEngine::createDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList) {
	drawableList.clear();


	// If STILL mode, stop here
	if (eventList.size() <= 1) {
		// Display nodes: Iterate through linked list and draw nodes
		addNodeDrawables(drawableList, SLLAnimStep());
		return;
	}


	// change visCur and visCurIndex
	animStepIndex = std::min(static_cast<int>(floor(time)), static_cast<int>(eventList.size()) - 1);
	time = std::min(std::max(time, 0.f), static_cast<float>(eventList.size()) - 0.0005f);
	SLLAnimStep eventSLL = eventList[animStepIndex];
	// if (time == static_cast<float>(eventList.size())) eventSLL = eventList.back();
	// Set parameters
	pSearch = eventSLL.pSearch; // Set pSearch in the event
	// Less safe: animInProgress = (time != static_cast<float>(eventList.size()) - 0.0005f);
	animInProgress = (abs(time - (static_cast<float>(eventList.size()) - 0.0005f)) > EPSILON);

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
	} else if (visMode == SLLVisMode::REMOVE_BEG || visMode == SLLVisMode::REMOVE_K) {
		addNodeDrawablesRemove(drawableList, eventSLL);
	} else {
		addNodeDrawables(drawableList, eventSLL);
	}


	// Display description for algorithm visualization
	auto descriptionText = std::make_unique<sf::Text>(font, eventSLL.text, descriptionFontSize);
	descriptionText->setFillColor(sf::Color::Black);
	descriptionText->setPosition(originPos - originPosDisplacement + descriptionTextPos);

	// Display animation step
	auto curBox = std::make_unique<sf::RectangleShape>(nodeValueRectSize);
	auto pCurText = std::make_unique<sf::Text>(font, "pCur", valueFontSize);
	switch (eventSLL.type) {
	case SLLAnimType::NONE:
		curBox->setPosition(originPos
			+ sf::Vector2f(0, 100)
			// + static_cast<float>(visCurIndex) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
			+ static_cast<float>(eventSLL.curIndex) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
		);
		pCurText->setPosition(curBox->getPosition());
		break;
	case SLLAnimType::CREATE_CUR:
		visCur = pHead;
		visCurIndex = 0;
		
		curBox->setPosition(originPos
			+ sf::Vector2f(0, 100)
			+ static_cast<float>(eventSLL.curIndex) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
		);
		pCurText->setPosition(curBox->getPosition());
		break;
	case SLLAnimType::MOVE_CUR_FORWARD:
		curBox->setPosition(originPos
			+ sf::Vector2f(0, 100)
			+ static_cast<float>(eventSLL.curIndex) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
			+ lerp(sf::Vector2f(0, 0), sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f), fract(time))
		);
		pCurText->setPosition(curBox->getPosition());
		break;
	default:
		curBox->setPosition(originPos
			+ sf::Vector2f(0, 100)
			+ static_cast<float>(eventSLL.curIndex) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
		);
		pCurText->setPosition(curBox->getPosition());
		break;
	}
	curBox->setFillColor(sf::Color::Transparent);
	curBox->setOutlineColor(sf::Color::Black);
	curBox->setOutlineThickness(2.f);
	pCurText->setFillColor(sf::Color::Black);
	// pCur arrow
	drawArrow(drawableList,
		curBox->getPosition() + sf::Vector2f(nodeValueRectSize.x/2, 0),
		curBox->getPosition() + sf::Vector2f(nodeValueRectSize.x/2, 0) - sf::Vector2f(0, 100) + sf::Vector2f(0, nodeRectSize.y)
	);

	drawableList.push_back(std::move(descriptionText));
	drawableList.push_back(std::move(curBox));
	drawableList.push_back(std::move(pCurText));

	std::cout << drawableList.size() << ' ' << time << " init done\n";
}



void SLLVisEngine::displayDrawables(std::unique_ptr<sfLayout>& sfmlLayout) {
	sfmlLayout->displayAll();
}





sf::Vector2f SLLVisEngine::lerp(sf::Vector2f v1, sf::Vector2f v2, float k) const {
	return v1 + (v2 - v1) * k;
}

void SLLVisEngine::drawArrow(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, sf::Vector2f v1, sf::Vector2f v2) const {
	float dx = v2.x - v1.x, dy = v2.y - v1.y;
	float len = sqrt(dx*dx + dy*dy);
	if (abs(len) < 1e-3) return; // Too small, don't draw

	float ux = dx / len, uy = dy / len;
	float px = -uy, py = ux;
	float height = sqrt(3.0) / 2 * arrowHeadSideLen;
	float baseCenterX = v2.x - height * ux;
    float baseCenterY = v2.y - height * uy;
    float leftX  = baseCenterX + (arrowHeadSideLen / 2) * px;
    float leftY  = baseCenterY + (arrowHeadSideLen / 2) * py;
    float rightX = baseCenterX - (arrowHeadSideLen / 2) * px;
    float rightY = baseCenterY - (arrowHeadSideLen / 2) * py;

    auto arrowBody = std::make_unique<sf::VertexArray>(sf::PrimitiveType::Lines, 2);
    (*arrowBody)[0].position = v1;
    (*arrowBody)[0].color = sf::Color::Black;
    (*arrowBody)[1].position = v2;
    (*arrowBody)[1].color = sf::Color::Black;

    auto arrowHead = std::make_unique<sf::VertexArray>(sf::PrimitiveType::Triangles, 3);
    (*arrowHead)[0].position = v2;
    (*arrowHead)[0].color = sf::Color::Black;
    (*arrowHead)[1].position = sf::Vector2f(leftX, leftY);
    (*arrowHead)[1].color = sf::Color::Black;
    (*arrowHead)[2].position = sf::Vector2f(rightX, rightY);
    (*arrowHead)[2].color = sf::Color::Black;

    drawableList.push_back(std::move(arrowBody));
    drawableList.push_back(std::move(arrowHead));
}

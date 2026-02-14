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
	pSearch = pHead->pNext;
}

SLLVisEngine::~SLLVisEngine() {
	clear();
}


void SLLVisEngine::increaseTime() {
	time += 0.005; // (ONLY FOR TESTING, FOR NOW)
	// if (time > 1.f) {
	// 	time = 0.f;
	// 	animStepIndex++;
	// }
}


void SLLVisEngine::resetParams() {
	visCur = nullptr; // cur in visualization (not in code)
	visCurIndex = 0; // cur index in visualization (not in code)

	animStepIndex = 0; // first step
	oldAnimStepIndex = 0; // first step
	time = 0;
}



void SLLVisEngine::createDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, std::vector<SLLAnimStep> eventList) {
	drawableList.clear();

	// Iterate through linked list and draw nodes
	int index = 0;
	SLLNode* cur = pHead;
	while (cur) {
		auto bigNodeBox = std::make_unique<sf::RectangleShape>(nodeRectSize);
		bigNodeBox->setFillColor(sf::Color::Transparent);
		bigNodeBox->setOutlineColor(
			(cur == visCur && visCur == pSearch && time >= 1) ? sf::Color::Green : sf::Color::Black
		);
		bigNodeBox->setOutlineThickness(2.f);
		bigNodeBox->setPosition(originPos 
			+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
		);
		
		auto smallNodeBox = std::make_unique<sf::RectangleShape>(nodeValueRectSize);
		smallNodeBox->setFillColor(sf::Color::Transparent);
		smallNodeBox->setOutlineColor(
			(cur == visCur && visCur == pSearch && time >= 1) ? sf::Color::Green : sf::Color::Black
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


	// If still mode, stop here
	if (eventList.empty()) return;


	// change visCur and visCurIndex
	animStepIndex = std::min(static_cast<int>(floor(time)), static_cast<int>(eventList.size()) - 1);
	SLLAnimStep eventSLL = eventList[animStepIndex];
	if (animStepIndex > oldAnimStepIndex) {
		if (eventList[oldAnimStepIndex].type == SLLAnimType::MOVE_CUR_FORWARD) {
			visCurIndex++;
			visCur = visCur->pNext;
		}
		oldAnimStepIndex = animStepIndex;
	}

	// Display animation step
	auto curBox = std::make_unique<sf::RectangleShape>(nodeValueRectSize);
	switch (eventSLL.type) {
	case SLLAnimType::NONE:
		curBox->setPosition(originPos
			+ sf::Vector2f(0, 100)
			+ static_cast<float>(visCurIndex) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
		);
		break;
	case SLLAnimType::CREATE_CUR:
		visCur = pHead;
		visCurIndex = 0;
		
		curBox->setPosition(originPos
			+ sf::Vector2f(0, 100)
			+ static_cast<float>(visCurIndex) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
		);
		break;
	case SLLAnimType::MOVE_CUR_FORWARD:
		curBox->setPosition(originPos
			+ sf::Vector2f(0, 100)
			+ static_cast<float>(visCurIndex) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
			+ lerp(sf::Vector2f(0, 0), sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f), time - floor(time))
		);
		break;
	}
	curBox->setFillColor(sf::Color::Transparent);
	curBox->setOutlineColor(sf::Color::Black);
	curBox->setOutlineThickness(2.f);

	drawableList.push_back(std::move(curBox));

	std::cout << drawableList.size() << ' ' << time << " init done\n";
}



void SLLVisEngine::displayDrawables(std::unique_ptr<sfLayout>& sfmlLayout) {
	sfmlLayout->displayAll();
}





sf::Vector2f SLLVisEngine::lerp(sf::Vector2f v1, sf::Vector2f v2, float k) const {
	return v1 + (v2 - v1) * k;
}

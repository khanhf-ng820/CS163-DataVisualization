#include "SLL/SLLVisEngine.h"





SLLVisEngine::SLLVisEngine(sf::RenderWindow& window, sf::Font& font)
	: window(window), font(font)
	, startingPos(sf::Vector2f(100, 100) - sf::Vector2f(window.getSize()) / 2.f)
{
	// Initialize linked list (ONLY FOR TESTING)
	pHead = new SLLNode{36, nullptr};
	pHead->pNext = new SLLNode{67, nullptr};
	pHead->pNext->pNext = new SLLNode{18, nullptr};
	pHead->pNext->pNext->pNext = new SLLNode{-1992, nullptr};
}

SLLVisEngine::~SLLVisEngine() {
	clear();
}


void SLLVisEngine::increaseTime() {
	time += 0.001; // (ONLY FOR TESTING, FOR NOW)
}



void SLLVisEngine::initDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, std::vector<SLLAnimStep> eventList) {
	drawableList.clear();

	// Iterate through linked list
	int index = 0;
	SLLNode* cur = pHead;
	while (cur) {
		auto bigNodeBox = std::make_unique<sf::RectangleShape>(nodeRectSize);
		bigNodeBox->setFillColor(sf::Color::Transparent);
		bigNodeBox->setOutlineColor((cur == pSearch) ? sf::Color::Green : sf::Color::Black);
		bigNodeBox->setOutlineThickness(2.f);
		bigNodeBox->setPosition(startingPos 
			+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
		);
		
		auto smallNodeBox = std::make_unique<sf::RectangleShape>(nodeValueRectSize);
		smallNodeBox->setFillColor(sf::Color::Transparent);
		smallNodeBox->setOutlineColor((cur == pSearch) ? sf::Color::Green : sf::Color::Black);
		smallNodeBox->setOutlineThickness(2.f);
		smallNodeBox->setPosition(startingPos 
			+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
		);

		auto valueText = std::make_unique<sf::Text>(font, std::to_string(cur->val), valueFontSize);
		valueText->setFillColor(sf::Color::Black);
		valueText->setPosition(startingPos 
			+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
		);

		auto linkLine = std::make_unique<sf::VertexArray>(sf::PrimitiveType::Lines, 2);
		(*linkLine)[0].position = startingPos 
			+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
			+ sf::Vector2f(nodeRectSize.x, nodeRectSize.y/2);
		(*linkLine)[0].color    = sf::Color::Black;
		(*linkLine)[1].position = startingPos 
			+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
			+ sf::Vector2f(nodeRectSize.x + linkArrowLength, nodeRectSize.y/2);
		(*linkLine)[1].color    = sf::Color::Black;

		drawableList.push_back(std::move(bigNodeBox));
		drawableList.push_back(std::move(smallNodeBox));
		drawableList.push_back(std::move(valueText));
		drawableList.push_back(std::move(linkLine));

		cur = cur->pNext;
		index++;
	}
	// Draw null node
	auto bigNullBox = std::make_unique<sf::RectangleShape>(nodeRectSize);
	bigNullBox->setFillColor(sf::Color::Transparent);
	bigNullBox->setOutlineColor(sf::Color::Black);
	bigNullBox->setOutlineThickness(2.f);
	bigNullBox->setPosition(startingPos 
		+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
	);

	auto nullDiagonal = std::make_unique<sf::VertexArray>(sf::PrimitiveType::Lines, 2);
	(*nullDiagonal)[0].position = startingPos 
		+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
		+ sf::Vector2f(nodeRectSize.x, 0.f);
	(*nullDiagonal)[0].color    = sf::Color::Black;
	(*nullDiagonal)[1].position = startingPos 
		+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
		+ sf::Vector2f(0.f, nodeRectSize.y);
	(*nullDiagonal)[1].color    = sf::Color::Black;

	auto nullText = std::make_unique<sf::Text>(font, "NULL", valueFontSize);
	nullText->setFillColor(sf::Color::Black);
	nullText->setPosition(startingPos 
		+ static_cast<float>(index) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
	);

	drawableList.push_back(std::move(bigNullBox));
	drawableList.push_back(std::move(nullDiagonal));
	drawableList.push_back(std::move(nullText));

	// std::cout << drawableList.size() << " init done\n";


	// SLLAnimStep eventSLL = eventList[animStepIndex];

	// switch (eventSLL.type) {
	// case SLLAnimType::NONE:
	// 	break;
	// }
}



void SLLVisEngine::displayDrawables(std::unique_ptr<sfLayout>& sfmlLayout) {
	sfmlLayout->displayAll();
}

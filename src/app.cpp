#include "../include/app.hpp"

//Private:

void Application::lineCreate(float x, float y, float len, float angle)
{
    Line l;
    l.create(sf::Vector2f(x,y), sf::Vector2f(x+len*cos(angle),y+len*sin(angle)));
    Lines.push_back(l);
}

void Application::treeCreate(float x, float y, float len, float angle,float len_div, float angle_div, float depth)
{
    //Line creation
    lineCreate(x,y,len,angle);
    
    if(depth == 0) return;

    // left
    treeCreate(x+len*cos(angle), y+len*sin(angle), len*len_div, angle-angle_div, len_div, angle_div, depth-1);

    // right
    treeCreate(x+len*cos(angle), y+len*sin(angle), len*len_div, angle+angle_div, len_div, angle_div, depth-1);
}

void Application::tunePositions()
{
    sf::Vector2f WinSize = sf::Vector2f(app.getSize());

    GenButtonSize = sf::Vector2f(WinSize.y/3.6, WinSize.y/14.4);
    GenButtonPos = sf::Vector2f(WinSize.x/4 - GenButtonSize.x/2, WinSize.y-100);
    
    GenerateB.create("GENERATE",0.6*GenButtonSize.y , GenButtonSize, GenButtonPos,sf::Color::Blue,sf::Color::Red);

    AngSliderSize = sf::Vector2f(WinSize.y/3.6, WinSize.y/16);
    AngSliderPos = sf::Vector2f(WinSize.x/4 - AngSliderSize.x, 100);

    AngleS.setHeadColor(sf::Color::Blue);
    AngleS.create(AngSliderSize.x,AngSliderSize.y,AngSliderPos);

    TreeSize.setCharacterSize(0.8*AngSliderSize.y);
    TreeSize.setFillColor(sf::Color::Blue);
    TreeSize.setOutlineColor(sf::Color::White);
    TreeSize.setOutlineThickness(2);
    TreeSize.setPosition(WinSize.x/4 + 10, 100);
}

//Public:

Application::Application(){}

Application::~Application(){}

void Application::run()
{
    app.create(sf::VideoMode(1280,720), "Fractal Tree");
    app.setFramerateLimit(30);
    std::vector<unsigned char> data = cf.read();
    GenerateB.loadFontFromMemory(data);

    font.loadFromMemory(data.data(),data.size());
    TreeSize.setFont(font);

    tunePositions();
    
    angle = 30;

    while(app.isOpen())
    {
        sf::Event ev;
        while(app.pollEvent(ev))
        {
            if(ev.type == sf::Event::Closed)
            {
                app.close();
            }
            if(ev.type == sf::Event::Resized)
            {
                sf::FloatRect viewArea(0,0,ev.size.width,ev.size.height);
                app.setView(sf::View(viewArea));
                tunePositions();
                generate = true;
            }
            
        }

        if(GenerateB.isButtonPressed(app))
            generate = true;

        if(generate)
        {
            if(!Lines.empty())
                Lines.clear();
            float RadAngle = M_PI * angle/180;
            treeCreate(app.getSize().x - app.getSize().x/3, app.getSize().y - 100, app.getSize().y/7.2, 4.71, 0.8, RadAngle, depth);
            generate = false;
        }

        AngleS.Update(app);

        depth = AngleS.getPercentValue() * 0.12;
        std::stringstream ss;
        ss << "Tree size: " << depth;
        if(ss.str() != TreeSize.getString())
        {
            TreeSize.setString(ss.str());
        }
        
        app.clear();

        GenerateB.displayTo(app);
        AngleS.displayTo(app);
        app.draw(TreeSize);
        
        if(!Lines.empty())
            for(auto l : Lines)
                l.drawTo(app);

        app.display();
    }
}
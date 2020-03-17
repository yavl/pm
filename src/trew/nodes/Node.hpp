#pragma once

#include <vector>
#include <string>
#include <memory>
#include <trew/Vector2.hpp>
#include <trew/actions/Actor.hpp>

namespace trew {
	class Node : public Actor {
	public:
		Node();
		Node(std::string name);
		virtual ~Node();
		virtual Node* getParent() const;
		virtual void draw() const;
		virtual void addChild(Node* node);
		virtual std::string getName() const;

		virtual float getX() const;
		virtual void setX(float x);
		virtual float getY() const;
		virtual void setY(float y);
		virtual void setXY(float x, float y);
		virtual float getWidth() const;
		virtual void setWidth(float width);
		virtual float getHeight() const;
		virtual void setHeight(float height);
		virtual void setSize(float width, float height);

		void act(float dt) override;
		void addAction(Action* action) override;
	private:
		Vector2 pos;
		Vector2 size;
		Node* parent;
		std::vector<std::unique_ptr<Node>> children;
		std::vector<std::unique_ptr<Action>> actions;
		std::string name;
	};
}

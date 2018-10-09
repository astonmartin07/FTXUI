#include "ftxui/dom/node.hpp"
#include "ftxui/dom/elements.hpp"

namespace ftxui {
namespace dom {

class Dim : public Node {
 public:
  Dim(Children children) : Node(std::move(children)) {}
  ~Dim() override {}

  void ComputeRequirement() override {
    Node::ComputeRequirement();
    requirement_ = children[0]->requirement();
  }

  void SetBox(Box box) override {
    Node::SetBox(box);
    children[0]->SetBox(box);
  }

  void Render(Screen& screen) override {
    Node::Render(screen);
    for (int y = box_.top; y <= box_.bottom; ++y) {
      for (int x = box_.left; x <= box_.right; ++x) {
        screen.PixelAt(x,y).dim = true; 
      }
    }
  }
};

std::unique_ptr<Node> dim(Child child) {
  return std::make_unique<Dim>(unpack(std::move(child)));
}

};  // namespace dom
};  // namespace ftxui

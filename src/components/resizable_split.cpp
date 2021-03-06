// cmake was not including this file so I directly copied it from the source code
// https://github.com/ArthurSonzogni/FTXUI/blob/master/src/ftxui/component/resizable_split.cpp

#include "ftxui/component/captured_mouse.hpp"  // for CapturedMouse
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/dom/elements.hpp"

namespace ftxui {
namespace {

class ResizableSplitLeftBase : public ComponentBase {
 public:
  ResizableSplitLeftBase(Component main, Component child, int* main_size)
      : main_(main), child_(child), main_size_(main_size) {
    Add(Container::Horizontal({
        main,
        child,
    }));
  }

  bool OnEvent(Event event) final {
    if (event.is_mouse())
      return OnMouseEvent(std::move(event));
    return ComponentBase::OnEvent(std::move(event));
  }

  bool OnMouseEvent(Event event) {
    if (captured_mouse_ && event.mouse().motion == Mouse::Released) {
      captured_mouse_.reset();
      return true;
    }

    if (event.mouse().button == Mouse::Left &&
        event.mouse().motion == Mouse::Pressed &&
        separator_box_.Contain(event.mouse().x, event.mouse().y) &&
        !captured_mouse_) {
      captured_mouse_ = CaptureMouse(event);
      return true;
    }

    if (captured_mouse_) {
      *main_size_ = event.mouse().x - global_box_.x_min;
      return true;
    }

    return ComponentBase::OnEvent(event);
  }

  Element Render() final {
    return hbox({
               main_->Render() | size(WIDTH, EQUAL, *main_size_),
               separator() | reflect(separator_box_),
               child_->Render() | xflex,
           }) |
           reflect(global_box_);
  };

 private:
  Component main_;
  Component child_;
  int* const main_size_;
  CapturedMouse captured_mouse_;
  Box separator_box_;
  Box global_box_;
};

class ResizableSplitRightBase: public ComponentBase {
 public:
  ResizableSplitRightBase(Component main, Component child, int* main_size)
      : main_(main), child_(child), main_size_(main_size) {
    Add(Container::Horizontal({
        child,
        main,
    }));
  }

  bool OnEvent(Event event) final {
    if (event.is_mouse())
      return OnMouseEvent(std::move(event));
    return ComponentBase::OnEvent(std::move(event));
  }

  bool OnMouseEvent(Event event) {
    if (captured_mouse_ && event.mouse().motion == Mouse::Released) {
      captured_mouse_.reset();
      return true;
    }

    if (event.mouse().button == Mouse::Left &&
        event.mouse().motion == Mouse::Pressed &&
        separator_box_.Contain(event.mouse().x, event.mouse().y) &&
        !captured_mouse_) {
      captured_mouse_ = CaptureMouse(event);
      return true;
    }

    if (captured_mouse_) {
      *main_size_ = global_box_.x_max - event.mouse().x;
      return true;
    }

    return ComponentBase::OnEvent(event);
  }

  Element Render() final {
    return hbox({
               child_->Render() | xflex,
               separator() | reflect(separator_box_),
               main_->Render() | size(WIDTH, EQUAL, *main_size_),
           }) |
           reflect(global_box_);
  };

 private:
  Component main_;
  Component child_;
  int* const main_size_;
  CapturedMouse captured_mouse_;
  Box separator_box_;
  Box global_box_;
};

class ResizableSplitTopBase: public ComponentBase {
 public:
  ResizableSplitTopBase(Component main, Component child, int* main_size)
      : main_(main), child_(child), main_size_(main_size) {
    Add(Container::Vertical({
        main,
        child,
    }));
  }

  bool OnEvent(Event event) final {
    if (event.is_mouse())
      return OnMouseEvent(std::move(event));
    return ComponentBase::OnEvent(std::move(event));
  }

  bool OnMouseEvent(Event event) {
    if (captured_mouse_ && event.mouse().motion == Mouse::Released) {
      captured_mouse_.reset();
      return true;
    }

    if (event.mouse().button == Mouse::Left &&
        event.mouse().motion == Mouse::Pressed &&
        separator_box_.Contain(event.mouse().x, event.mouse().y) &&
        !captured_mouse_) {
      captured_mouse_ = CaptureMouse(event);
      return true;
    }

    if (captured_mouse_) {
      *main_size_ = event.mouse().y - global_box_.y_min;
      return true;
    }

    return ComponentBase::OnEvent(event);
  }

  Element Render() final {
    return vbox({
               main_->Render() | size(HEIGHT, EQUAL, *main_size_),
               separator() | reflect(separator_box_),
               child_->Render() | yflex,
           }) |
           reflect(global_box_);
  };

 private:
  Component main_;
  Component child_;
  int* const main_size_;
  CapturedMouse captured_mouse_;
  Box separator_box_;
  Box global_box_;
};

class ResizableSplitBottomBase: public ComponentBase {
 public:
  ResizableSplitBottomBase(Component main, Component child, int* main_size)
      : main_(main), child_(child), main_size_(main_size) {
    Add(Container::Vertical({
        child,
        main,
    }));
  }

  bool OnEvent(Event event) final {
    if (event.is_mouse())
      return OnMouseEvent(std::move(event));
    return ComponentBase::OnEvent(std::move(event));
  }

  bool OnMouseEvent(Event event) {
    if (captured_mouse_ && event.mouse().motion == Mouse::Released) {
      captured_mouse_.reset();
      return true;
    }

    if (event.mouse().button == Mouse::Left &&
        event.mouse().motion == Mouse::Pressed &&
        separator_box_.Contain(event.mouse().x, event.mouse().y) &&
        !captured_mouse_) {
      captured_mouse_ = CaptureMouse(event);
      return true;
    }

    if (captured_mouse_) {
      *main_size_ = global_box_.y_max - event.mouse().y;
      return true;
    }

    return ComponentBase::OnEvent(event);
  }

  Element Render() final {
    return vbox({
               child_->Render() | yflex,
               separator() | reflect(separator_box_),
               main_->Render() | size(HEIGHT, EQUAL, *main_size_),
           }) |
           reflect(global_box_);
  };

 private:
  Component main_;
  Component child_;
  int* const main_size_;
  CapturedMouse captured_mouse_;
  Box separator_box_;
  Box global_box_;
};

}  // namespace

/// @brief An horizontal split in between two components, configurable using the
/// mouse.
/// @param main The main component of size |main_size|, on the left.
/// @param back The back component taking the remaining size, on the right.
/// @param main_size The size of the |main| component.
/// @ingroup component
///
/// ### Example
///
/// ```cpp
/// auto screen = ScreenInteractive::Fullscreen();
/// int left_size = 10;
/// auto left = Renderer([] { return text(L"Left") | center;});
/// auto right = Renderer([] { return text(L"right") | center;});
/// auto split = ResizableSplitLeft(left, right, &left_size);
/// screen.Loop(split);
/// ```
///
/// ### Output
///
/// ```bash
///           ???           
///    left   ???   right   
///           ???           
/// ```
Component ResizableSplitLeft(Component main, Component back, int* main_size) {
  return Make<ResizableSplitLeftBase>(std::move(main), std::move(back), main_size);
}

/// @brief An horizontal split in between two components, configurable using the
/// mouse.
/// @param main The main component of size |main_size|, on the right.
/// @param back The back component taking the remaining size, on the left.
/// @param main_size The size of the |main| component.
/// @ingroup component
///
/// ### Example
///
/// ```cpp
/// auto screen = ScreenInteractive::Fullscreen();
/// int right_size = 10;
/// auto left = Renderer([] { return text(L"Left") | center;});
/// auto right = Renderer([] { return text(L"right") | center;});
/// auto split = ResizableSplitRight(right, left, &right_size);
/// screen.Loop(split);
/// ```
///
/// ### Output
///
/// ```bash
///           ???
///    left   ???   right
///           ???
/// ```
Component ResizableSplitRight(Component main, Component back, int* main_size) {
  return Make<ResizableSplitRightBase>(std::move(main), std::move(back),
                                       main_size);
}

/// @brief An vertical split in between two components, configurable using the
/// mouse.
/// @param main The main component of size |main_size|, on the top.
/// @param back The back component taking the remaining size, on the bottom.
/// @param main_size The size of the |main| component.
/// @ingroup component
///
/// ### Example
///
/// ```cpp
/// auto screen = ScreenInteractive::Fullscreen();
/// int top_size = 1;
/// auto top = Renderer([] { return text(L"Top") | center;});
/// auto bottom = Renderer([] { return text(L"Bottom") | center;});
/// auto split = ResizableSplitTop(top, bottom, &top_size);
/// screen.Loop(split);
/// ```
///
/// ### Output
///
/// ```bash
///    top
/// ????????????????????????????????????
///    bottom
/// ```
Component ResizableSplitTop(Component main, Component back, int* main_size) {
  return Make<ResizableSplitTopBase>(std::move(main), std::move(back), main_size);
}

/// @brief An vertical split in between two components, configurable using the
/// mouse.
/// @param main The main component of size |main_size|, on the bottom.
/// @param back The back component taking the remaining size, on the top.
/// @param main_size The size of the |main| component.
/// @ingroup component
///
/// ### Example
///
/// ```cpp
/// auto screen = ScreenInteractive::Fullscreen();
/// int bottom_size = 1;
/// auto top = Renderer([] { return text(L"Top") | center;});
/// auto bottom = Renderer([] { return text(L"Bottom") | center;});
/// auto split = ResizableSplit::Bottom(bottom, top, &bottom_size);
/// screen.Loop(split);
/// ```
///
/// ### Output
///
/// ```bash
///    top
/// ????????????????????????????????????
///    bottom
/// ```
Component ResizableSplitBottom(Component main, Component back, int* main_size) {
  return Make<ResizableSplitBottomBase>(std::move(main), std::move(back), main_size);
}
}  // namespace ftxui
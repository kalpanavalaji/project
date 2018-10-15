// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ash/common/wm/window_positioner.h"

#include <string>

#include "ash/common/material_design/material_design_controller.h"
#include "ash/common/wm/window_positioner.h"
#include "ash/common/wm/window_state.h"
#include "ash/shell.h"
#include "ash/shell/toplevel_window.h"
#include "ash/test/ash_md_test_base.h"
#include "ash/test/test_shell_delegate.h"
#include "ash/wm/window_state_aura.h"
#include "base/strings/string_number_conversions.h"
#include "ui/aura/window_event_dispatcher.h"
#include "ui/display/screen.h"
#include "ui/views/widget/widget.h"
#include "ui/views/widget/widget_delegate.h"

namespace ash {

using WindowPositionerTest = test::AshMDTestBase;

INSTANTIATE_TEST_CASE_P(
    /* prefix intentionally left blank due to only one parameterization */,
    WindowPositionerTest,
    testing::Values(MaterialDesignController::NON_MATERIAL,
                    MaterialDesignController::MATERIAL_NORMAL,
                    MaterialDesignController::MATERIAL_EXPERIMENTAL));

TEST_P(WindowPositionerTest, OpenMaximizedWindowOnSecondDisplay) {
  if (!SupportsMultipleDisplays())
    return;
  const int height_offset = GetMdMaximizedWindowHeightOffset();
  // Tests that for a screen that is narrower than kForceMaximizeWidthLimit
  // a new window gets maximized.
  UpdateDisplay("400x400,500x500");
  Shell::GetInstance()->set_target_root_window(Shell::GetAllRootWindows()[1]);
  shell::ToplevelWindow::CreateParams params;
  params.can_resize = true;
  params.can_maximize = true;
  views::Widget* widget = shell::ToplevelWindow::CreateToplevelWindow(params);
  EXPECT_EQ(gfx::Rect(400, 0, 500, 453 + height_offset).ToString(),
            widget->GetWindowBoundsInScreen().ToString());
}

TEST_P(WindowPositionerTest, OpenDefaultWindowOnSecondDisplay) {
  if (!SupportsMultipleDisplays())
    return;
#if defined(OS_WIN)
  ash::WindowPositioner::SetMaximizeFirstWindow(true);
#endif
  UpdateDisplay("400x400,1400x900");
  aura::Window* second_root_window = Shell::GetAllRootWindows()[1];
  Shell::GetInstance()->set_target_root_window(second_root_window);
  shell::ToplevelWindow::CreateParams params;
  params.can_resize = true;
  params.can_maximize = true;
  views::Widget* widget = shell::ToplevelWindow::CreateToplevelWindow(params);
  gfx::Rect bounds = widget->GetWindowBoundsInScreen();
#if defined(OS_WIN)
  EXPECT_TRUE(widget->IsMaximized());
#else
  // The window should be in the 2nd display with the default size.
  EXPECT_EQ("300x300", bounds.size().ToString());
#endif
  EXPECT_TRUE(display::Screen::GetScreen()
                  ->GetDisplayNearestWindow(second_root_window)
                  .bounds()
                  .Contains(bounds));
}

// Tests that second window inherits first window's maximized state as well as
// its restore bounds.
// TODO(msw): Broken on Windows. http://crbug.com/584038
#if defined(OS_CHROMEOS)
TEST_P(WindowPositionerTest, SecondMaximizedWindowHasProperRestoreSize) {
  const int height_offset = GetMdMaximizedWindowHeightOffset();
  UpdateDisplay("1400x900");
  shell::ToplevelWindow::CreateParams params;
  params.can_resize = true;
  params.can_maximize = true;
  views::Widget* widget1 = shell::ToplevelWindow::CreateToplevelWindow(params);
  gfx::Rect bounds = widget1->GetWindowBoundsInScreen();

  // The window should have default size.
  EXPECT_FALSE(widget1->IsMaximized());
  EXPECT_EQ("300x300", bounds.size().ToString());
  widget1->Maximize();

  // The window should be maximized.
  bounds = widget1->GetWindowBoundsInScreen();
  EXPECT_TRUE(widget1->IsMaximized());
  EXPECT_EQ(gfx::Rect(0, 0, 1400, 853 + height_offset).ToString(),
            bounds.ToString());

  // Create another window
  views::Widget* widget2 = shell::ToplevelWindow::CreateToplevelWindow(params);

  // The second window should be maximized.
  bounds = widget2->GetWindowBoundsInScreen();
  EXPECT_TRUE(widget2->IsMaximized());
  EXPECT_EQ(gfx::Rect(0, 0, 1400, 853 + height_offset).ToString(),
            bounds.ToString());

  widget2->Restore();
  // Second window's restored size should be set to default size.
  bounds = widget2->GetWindowBoundsInScreen();
  EXPECT_EQ("300x300", bounds.size().ToString());
}
#endif  // defined(OS_CHROMEOS)

namespace {

// A WidgetDelegate that returns the out of display saved bounds.
class OutOfDisplayDelegate : public views::WidgetDelegate {
 public:
  explicit OutOfDisplayDelegate(views::Widget* widget) : widget_(widget) {}
  ~OutOfDisplayDelegate() override {}

  // Overridden from WidgetDelegate:
  void DeleteDelegate() override { delete this; }
  views::Widget* GetWidget() override { return widget_; }
  const views::Widget* GetWidget() const override { return widget_; }
  bool GetSavedWindowPlacement(const views::Widget* widget,
                               gfx::Rect* bounds,
                               ui::WindowShowState* show_state) const override {
    bounds->SetRect(450, 10, 100, 100);
    *show_state = ui::SHOW_STATE_NORMAL;
    return true;
  }

 private:
  views::Widget* widget_;

  DISALLOW_COPY_AND_ASSIGN(OutOfDisplayDelegate);
};

}  // namespace

TEST_P(WindowPositionerTest, EnsureMinimumVisibility) {
  if (!SupportsHostWindowResize())
    return;

  UpdateDisplay("400x400");
  views::Widget* widget = new views::Widget();
  views::Widget::InitParams params(views::Widget::InitParams::TYPE_WINDOW);
  params.delegate = new OutOfDisplayDelegate(widget);
  params.context = Shell::GetPrimaryRootWindow();
  widget->Init(params);
  widget->SetBounds(gfx::Rect(450, 10, 100, 100));
  wm::GetWindowState(widget->GetNativeView())->set_minimum_visibility(true);
  widget->Show();
  // Make sure the bounds is adjusted to be inside the work area.
  EXPECT_EQ("375,10 100x100", widget->GetWindowBoundsInScreen().ToString());
  widget->CloseNow();
}

// In general case on first run the browser window will be maximized only for
// low resolution screens (width < 1366). In case of big screens the browser is
// opened being not maximized. To enforce maximization for all screen
// resolutions, one can set "ForceMaximizeBrowserWindowOnFirstRun"
// policy. In the following tests we check if the window will be opened in
// maximized mode for low and high resolution when this policy is set.
TEST_P(WindowPositionerTest, FirstRunMaximizeWindowHighResloution) {
  const int width = ash::WindowPositioner::GetForceMaximizedWidthLimit() + 100;
  // Set resolution to 1466x300.
  const std::string resolution = base::IntToString(width) + "x300";
  UpdateDisplay(resolution);
  gfx::Rect bounds_in_out(0, 0, 320, 240);  // Random bounds.
  ui::WindowShowState show_state_out = ui::SHOW_STATE_DEFAULT;

  test::TestShellDelegate* const delegate =
      static_cast<test::TestShellDelegate*>(Shell::GetInstance()->delegate());
  delegate->SetForceMaximizeOnFirstRun(true);

  WindowPositioner::GetBoundsAndShowStateForNewWindow(
      nullptr, false, ui::SHOW_STATE_DEFAULT, &bounds_in_out, &show_state_out);

  EXPECT_EQ(show_state_out, ui::SHOW_STATE_MAXIMIZED);
}

// For detail see description of FirstRunMaximizeWindowHighResloution.
TEST_P(WindowPositionerTest, FirstRunMaximizeWindowLowResolution) {
  const int width = ash::WindowPositioner::GetForceMaximizedWidthLimit() - 100;
  // Set resolution to 1266x300.
  const std::string resolution = base::IntToString(width) + "x300";
  UpdateDisplay(resolution);
  gfx::Rect bounds_in_out(0, 0, 320, 240);  // Random bounds.
  ui::WindowShowState show_state_out = ui::SHOW_STATE_DEFAULT;

  test::TestShellDelegate* const delegate =
      static_cast<test::TestShellDelegate*>(Shell::GetInstance()->delegate());
  delegate->SetForceMaximizeOnFirstRun(true);

  WindowPositioner::GetBoundsAndShowStateForNewWindow(
      nullptr, false, ui::SHOW_STATE_DEFAULT, &bounds_in_out, &show_state_out);

  EXPECT_EQ(show_state_out, ui::SHOW_STATE_MAXIMIZED);
}

TEST_P(WindowPositionerTest, IgnoreFullscreenInAutoRearrange) {
  if (!SupportsHostWindowResize())
    return;
  // Set bigger than 1366 so that the new window is opened in normal state.
  UpdateDisplay("1400x800");

  // 1st window mimics fullscreen browser window behavior.
  shell::ToplevelWindow::CreateParams params;
  params.can_resize = true;
  params.can_maximize = true;
  views::Widget* widget1 = shell::ToplevelWindow::CreateToplevelWindow(params);
  wm::WindowState* managed_state =
      wm::GetWindowState(widget1->GetNativeWindow());
  EXPECT_TRUE(managed_state->window_position_managed());
  EXPECT_EQ("300x300", widget1->GetWindowBoundsInScreen().size().ToString());
  widget1->SetFullscreen(true);
  ASSERT_EQ("1400x800", widget1->GetWindowBoundsInScreen().size().ToString());

  // 2nd window mimics windowed v1 app.
  params.use_saved_placement = false;
  views::Widget* widget2 = shell::ToplevelWindow::CreateToplevelWindow(params);
  wm::WindowState* state_2 = wm::GetWindowState(widget2->GetNativeWindow());
  EXPECT_TRUE(state_2->window_position_managed());
  EXPECT_EQ("300x300", widget2->GetWindowBoundsInScreen().size().ToString());

  // Restores to the original size.
  widget1->SetFullscreen(false);
  ASSERT_EQ("300x300", widget1->GetWindowBoundsInScreen().size().ToString());

  // Closing 2nd widget triggers the rearrange logic but the 1st
  // widget should stay in the current size.
  widget2->CloseNow();
  ASSERT_EQ("300x300", widget1->GetWindowBoundsInScreen().size().ToString());
}

}  // namespace ash

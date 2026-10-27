--
-- Cocos2dx Event
--
ns.UITexType = {Local = 0, Plist = 1}

ns.TouchEventType = {began = 0, moved = 1, ended = 2, canceled = 3}

ns.LoadingBarType = {left = 0, right = 1}

ns.CheckBoxEventType = {selected = 0, unselected = 1}

ns.SliderEventType = {percent_changed = 0}

ns.TextFiledEventType = {
    attach_with_ime = 0,
    detach_with_ime = 1,
    insert_text = 2,
    delete_backward = 3
}

ns.LayoutBackGroundColorType = {none = 0, solid = 1, gradient = 2}

ns.LayoutType = {
    absolute = 0,
    linearVertical = 1,
    linearHorizontal = 2,
    relative = 3
}

ns.UILinearGravity = {
    none = 0,
    left = 1,
    top = 2,
    right = 3,
    bottom = 4,
    centerVertical = 5,
    centerHorizontal = 6
}

ns.SCROLLVIEW_DIR = {none = 0, vertical = 1, horizontal = 2, both = 3}

ns.PageViewEventType = {turning = 0}

ns.ListViewEventType = {init_child = 0, update_child = 1}

ns.ListViewDirection = {none = 0, vertical = 1, horizontal = 2}

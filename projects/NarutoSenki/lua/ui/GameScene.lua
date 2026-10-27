--
-- GameScene
--
local gameScene = GameScene

function GameScene:init()
    log('Initial GameScene...')

    self.cheats = 0
    self.pushMenu = nil
    self.logoMenu = nil
    self.introLayer = nil

    if not save.getBool('isHavingSave') then
        save.bool('isHavingSave', true)
        save.bool('isBGM', true)
        save.bool('isVoice', true)
        save.flush()
    end

    self.introLayer = display.newLayer()

    local logoImage = display.newSprite('zakume.png', display.width / 2,
                                        display.height / 2)

    local seq = transition.sequence({
        CCFadeIn:create(1.25), CCFadeOut:create(1.25),
        CCCallFunc:create(handler(self, GameScene.onLogo))
    })
    logoImage:runAction(seq)

    self.introLayer:addChild(logoImage)
    self:addChild(self.introLayer)

    _G.platform = GameScene:getPlatform()
    log('platform: ' .. _G.platform)
end

function GameScene:onLogo()
    local logo_btn = ui.newImageMenuItem({
        image = 'logo.png',
        listener = handler(self, GameScene.onLogoClick)
    })
    logo_btn:setAnchorPoint(0.5, 0.5)

    self.logoMenu = ui.newMenu({logo_btn})
    self.logoMenu:setPosition(display.width / 2, display.height -
                                  logo_btn:getContentSize().height / 2)
    self.introLayer:addChild(self.logoMenu)

    audio.playSound(ns.menu.MENU_INTRO)

    local seq = transition.sequence({
        CCFadeIn:create(1.5),
        CCCallFunc:create(
            function() return audio.playSound(ns.menu.MENU_INTRO2) end),
        CCDelayTime:create(2.0),
        CCCallFunc:create(handler(self, GameScene.onFinish))
    })
    logo_btn:runAction(seq)
end

function GameScene:onLogoClick()
    self.cheats = self.cheats + 1

    if self.cheats == 7 then
        audio.stopAllSounds()
        self.logoMenu:removeFromParent()

        local logo_btn = ui.newImageMenuItem({
            image = 'logo2.png',
            listener = handler(self, GameScene.onLogoClick)
        })
        logo_btn:setAnchorPoint(0.5, 0.5)

        self.logoMenu = ui.newMenu({logo_btn})
        self.logoMenu:setPosition(display.width / 2, display.height -
                                      logo_btn:getContentSize().height / 2)
        self.introLayer:addChild(self.logoMenu, 3)

        self:onFinish()
    elseif self.cheats >= 7 then
        audio.stopAllSounds()
        audio.stopMusic(true)
        audio.playSound(ns.menu.LOGO_CLICK)
    end
end

function GameScene:onFinish()
    if not self.pushMenu then
        audio.playMusic(ns.music.INTRO_MUSIC, true)

        local btm_btn = ui.newImageMenuItem({
            image = 'push_start.png',
            listener = handler(self, GameScene.onPush)
        })
        self.pushMenu = ui.newMenu({btm_btn})
        self.pushMenu:setPosition(display.width / 2, display.height / 2 - 100)
        self.introLayer:addChild(self.pushMenu)

        local fade = CCFadeOut:create(0.5)
        local seq = transition.sequence({fade, fade:reverse()})
        btm_btn:runAction(CCRepeatForever:create(seq))
    end
end

function GameScene:onPush()
    tools.initSqliteDB()

    audio.stopMusic(true)
    -- Play sound and delayed change scene
    -- Cleanup audio engine in StartMenu
    audio.playSound(ns.menu.CONFIRM)

    local menuScene = CCScene:create()
    local menuLayer = StartMenu:create()
    menuLayer:setCheats(self.cheats)
    menuScene:addChild(menuLayer)

    -- for auto call c++ layer StartMenu::init after lua called
    hook.registerInitHandlerOnly(menuLayer)

    director.replaceSceneWithFade(menuScene, 1.0)
end

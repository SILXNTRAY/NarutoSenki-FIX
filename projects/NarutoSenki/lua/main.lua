require 'config'

local function main()
    -- avoid memory leak
    collectgarbage('setpause', 100)
    collectgarbage('setstepmul', 5000)
    log('--- Loaded Lua Scripts ---')

    local gameScene = GameScene:create()
    hook.registerInitHandlerOnly(gameScene)
    CCDirector:sharedDirector():runWithScene(gameScene)
end

xpcall(main, __G__TRACKBACK__)

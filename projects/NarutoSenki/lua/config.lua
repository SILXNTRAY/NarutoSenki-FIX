--
-- Config
--

-- design resoluation configuration
CONFIG_SCREEN_WIDTH     = 570
CONFIG_SCREEN_HEIGHT    = 320
CONFIG_SCREEN_AUTOSCALE = 'FIXED_HEIGHT'

require 'framework.init'

-- if DEBUG == 0 then
log = function(...) print(string.format(...)) end

-- for CCLuaEngine traceback
function __G__TRACKBACK__(msg)
    print('----------------------------------------')
    print('LUA ERROR: ' .. tostring(msg) .. '\n')
    print(debug.traceback())
    print('----------------------------------------')
end

ns = {}

-- Load utils
require 'utils.hook'
require 'utils.event'
require 'utils.utils'
require 'utils.save'
require 'utils.math'

require 'core.init'

-- UI Module
require 'ui.init'

-- Character Module
require 'class.basic'

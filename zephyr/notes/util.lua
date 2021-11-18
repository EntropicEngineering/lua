-- Adapted from https://gist.github.com/justnom/9816256
function table_to_string(tbl)
    local result = "{"
    for k, v in pairs(tbl) do
        -- Check the key type (ignore any numerical keys - assume its an array)
        if type(k) == "string" then
            result = result..k.."="
        else
        	result = result.."<"..k..">="
        end

        -- Check the value type
        if type(v) == "table" then
            result = result..table_to_string(v)
        elseif type(v) == "boolean" or type(v) == "number" then
            result = result..tostring(v)
        elseif type(v) == "table" then
            result = result.."\""..v.."\""
        else
            result = result.."<"..v..">"
        end
        result = result..","
    end
    return result.."}"
end

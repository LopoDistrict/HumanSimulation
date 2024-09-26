def get_model(id, line):
    path = "../../data/memory/model/" + id + ".dmem"    
    result = ""
    with open(path) as file:
        return file.readlines()[line]

def get_line_equivalent(id, line):
    lineFile = str(get_model(id, line))
    path = "../../data/memory/model/" + id + ".dmem"
    value = ""    
    for i in lineFile:
        if i == "=":
            return value
        value += i
    
def get_value(id, line):
    value = get_line_equivalent(id, line)
    model = get_model(id, line)
    return model[len(value)+1:] 

print(get_model('0kfpdq75', 1))
print(get_line_equivalent('0kfpdq75', 1))
print(get_value('0kfpdq75', 1))     

            
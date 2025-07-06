def visitTuple(*list):
    print(f"{list.__class__}")
    for item in list:
        print(f"{item} \t type: \t {item.__class__}")
    print(f"{len(list)} items in parameter")

def visitDictionary(**list):
    print(f"{list.__class__}")
    for key, value in list.items():
        print(f"{key} \t type: \t {key.__class__}")
        print(f"{value} \t type: \t {value.__class__}")
    print(f"{len(list)} items in parameter")


def fn():
    print("hello world!")
    visitTuple(3, "abc")
    print("\n")
    visitDictionary(key1=3, key2="abc", key3=[1,2,3], key4=(1, "a",3), key5={"a": 1, "b": "str3", "c-":'z'})
    # help(str.__len__)
    # help(str.count)
    s = 1 + 20
    print(s)
    print("the end")

if __name__ == "__main__":
    fn()



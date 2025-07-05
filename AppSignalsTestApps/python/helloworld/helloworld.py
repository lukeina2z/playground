def fn():
    print("hello world!")
    help(str.__len__)
    help(str.count)
    print("the end")

if __name__ == "__main__":
    fn()
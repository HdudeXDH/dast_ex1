import random

def gen(leng,removables_amount=0):
    t =list(set([random.randint(-10000, 10000) for i in range(leng)]))
    random.shuffle(t)
    r= ", ".join([str(i) for i in t])
    random.shuffle(t)
    removables = ", ".join([str(i) for i in t[:removables_amount]])
    return r, removables

def generate_add_remove_tests(amount, length, remove_length):
    for i in range(amount):
        r, removables = gen(length,remove_length)
        arr_name = f"tr{i}_source_{amount}_{length}_{remove_length}"
        remove_arr_name = f"tr{i}_remov_{amount}_{length}_{remove_length}"
        print(f"""
        std::vector<int> {arr_name}({{{r}}});
        std::vector<int> {remove_arr_name}({{{removables}}});
        assert(true == test_vector_of_inserts_inorder({arr_name}, false, {remove_arr_name}));""")

def generate_memory_tests(amount, length, remove_length):
    for i in range(amount):
        r, removables = gen(length,remove_length)
        arr_name = f"tr{i}_hard_source_{amount}_{length}_{remove_length}"
        remove_arr_name = f"tr{i}_hard_remov_{amount}_{length}_{remove_length}"
        print(f"""
        std::vector<int> {arr_name}({{{r}}});
        std::vector<int> {remove_arr_name}({{{removables}}});
        assert(true == test_deletion({arr_name}, {remove_arr_name}));""")
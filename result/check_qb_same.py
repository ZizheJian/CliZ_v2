def compare_and_list_difference(file1_path, file2_path):
    try:
        # 打开第一个文件
        with open(file1_path, 'r') as file1:
            # 读取第一个文件的内容
            content1 = file1.readlines()

        # 打开第二个文件
        with open(file2_path, 'r') as file2:
            # 读取第二个文件的内容
            content2 = file2.readlines()

        # 比较文件内容并列出不同的行
        for line_num, (line1, line2) in enumerate(zip(content1, content2), start=1):
            if line1 != line2:
                print(f"行 {line_num}: 文件1: {line1.strip()}, 文件2: {line2.strip()}")

    except FileNotFoundError:
        print("文件不存在。")

# 用法示例
file1_path = "qb.txt"
file2_path = "/home/jzz/compress/SZ3/result/qb.txt"
compare_and_list_difference(file1_path, file2_path)
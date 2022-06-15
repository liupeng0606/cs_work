import tensorflow as tf
from tensorflow.python.framework import ops
ops.reset_default_graph()
import imageio


from utils import compute_content_cost, compute_style_cost, total_cost, generate_noise_image, save_image, \
    reshape_and_normalize_image, load_vgg_model


def transfer(num_iterations=200):
    # 重置图表
    tf.reset_default_graph()

    # 开始互动会话
    sess = tf.InteractiveSession()

    # 通过向 content_image 添加随机噪声来初始化噪声图像
    generated_image = generate_noise_image(content_image)

    # 加载 VGG19 模型
    model = load_vgg_model("pretrained-model/imagenet-vgg-verydeep-19.mat")

    # 将内容图像分配为 VGG 模型的输入。
    sess.run(model['input'].assign(content_image))

    # 选择层conv4_2的输出张量
    out = model['conv4_2']

    # 将 a_C 设置为我们选择的层的隐藏层激活
    a_C = sess.run(out)

    # 将 a_G 设置为来自同一层的隐藏层激活。在这里，a_G 引用了模型['conv4_2']
    # 并且尚未评估。稍后在代码中，将图像 G 指定为模型输入，这样
    # 当运行会话时，这将是从适当的层提取的激活，以 G 作为输入。
    a_G = out

    # 计算内容成本
    J_content = compute_content_cost(a_C, a_G)

    # 将模型的输入分配为“风格”图像
    sess.run(model['input'].assign(style_image))

    # 计算样式成本
    J_style = compute_style_cost(sess, model)

    J = total_cost(J_content, J_style, alpha, beta)  # 10,40

    # define optimizer (1 line)
    optimizer = tf.train.AdamOptimizer(2.0)

    # define train_step (1 line)
    train_step = optimizer.minimize(J)

    # Initialize global variables (you need to run the session on the initializer)
    sess.run(tf.global_variables_initializer())

    # Run the noisy input image (initial generated image) through the model. Use assign().
    sess.run(model["input"].assign(generated_image))

    for i in range(num_iterations):

        # 在 train_step 上运行会话以最小化总成本
        sess.run(train_step)

        # 通过在当前模型上运行会话来计算生成的图像['input']
        generated_image = sess.run(model["input"])

        # 每 20 次迭代打印一次。
        if i % 20 == 0:
            Jt, Jc, Js = sess.run([J, J_content, J_style])
            print("Iteration " + str(i) + " :")
            print("total cost = " + str(Jt))
            print("content cost = " + str(Jc))
            print("style cost = " + str(Js))

            # 将当前生成的图像保存在“/output”目录中
            save_image("images/" + str(i) + ".png", generated_image)

    # 保存最后生成的图像

    save_image("images/output.png", generated_image)

    return generated_image


if __name__ == '__main__':
    # 参数
    alpha = 10
    beta = 40
    iterations = 200

    content_image = imageio.imread("images/content.jpg")
    content_image = reshape_and_normalize_image(content_image)
    style_image = imageio.imread("images/style.jpg")
    style_image = reshape_and_normalize_image(style_image)
    generated_image = generate_noise_image(content_image)

    transfer()
 #include "mainmenu.h"

MainMenu::MainMenu() : material("polygon3d"), poly() {
	//client->insert(new Game());

    srand(glfwGetTime());
    unsigned int amount = 1000;

    for (unsigned int i = 0; i < amount; i++) {
        glm::mat4 model = glm::mat4(1.0f);

        model = glm::translate(model, glm::vec3(rand() % 100, -(rand() % 10), rand() % 100));

        model = glm::scale(model, glm::vec3(1.0f));

        model = glm::rotate(model, float(rand() % 360), glm::vec3(0.4f, 0.6f, 0.8f));

        poly.new_instance(model);
    }

    poly.delete_instance(0);
}

MainMenu::~MainMenu() {

}

void MainMenu::on_connect() {

}

void MainMenu::on_disconnect() {

}

void MainMenu::update() {
	material.use();

    //glm::mat4 View = glm::mat4(1.0f);
    //View = glm::translate(View, glm::vec3((float)glfwGetTime(), 0.0f, 0.0f));
    //View = glm::rotate(View, (float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f));

    glm::vec2 Size = engine::engine->window.get_size();

    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), Size.x / Size.y, 0.1f, 1000000.0f);

    glm::mat4 View = glm::lookAt(
        glm::vec3(0, 10, 0),
        glm::vec3(20, 0, 20),
        glm::vec3(0, 1, 0)
    );

    View = glm::translate(View, glm::vec3(-2.0f * glfwGetTime(), 0, -2.0f * glfwGetTime()));

    glm::mat4 Model = glm::mat4(1.0f);

    glm::mat4 MVP = Projection * View * Model;

    material.set_mat4("mvp", MVP);

	poly.draw();
}
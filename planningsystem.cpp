#include "planningsystem.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>

PlanningSystem::PlanningSystem(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Interface pour ajouter des tâches
    QHBoxLayout *addTaskLayout = new QHBoxLayout;
    taskLineEdit = new QLineEdit(this);
    QPushButton *addTaskButton = new QPushButton("Ajouter", this);
    connect(addTaskButton, &QPushButton::clicked, this, &PlanningSystem::addTask);
    addTaskLayout->addWidget(taskLineEdit);
    addTaskLayout->addWidget(addTaskButton);

    mainLayout->addLayout(addTaskLayout);

    // Liste des tâches planifiées
    taskListWidget = new QListWidget(this);
    mainLayout->addWidget(taskListWidget);

    // Bouton pour supprimer une tâche sélectionnée
    QPushButton *removeTaskButton = new QPushButton("Supprimer la tâche sélectionnée", this);
    connect(removeTaskButton, &QPushButton::clicked, this, &PlanningSystem::removeTask);
    mainLayout->addWidget(removeTaskButton);

    setLayout(mainLayout);
}

void PlanningSystem::addTask() {
    QString task = taskLineEdit->text();
    if (!task.isEmpty()) {
        taskListWidget->addItem(task);
        taskLineEdit->clear();
    } else {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer une tâche valide.");
    }
}

void PlanningSystem::removeTask() {
    QListWidgetItem *selectedItem = taskListWidget->currentItem();
    if (selectedItem) {
        delete selectedItem;
    } else {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner une tâche à supprimer.");
    }
}

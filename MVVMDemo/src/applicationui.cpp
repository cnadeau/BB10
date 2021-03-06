/*
 * Copyright (c) 2013 Macadamian Technologies Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "applicationui.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include "Model.h"
#include "ViewModel.h"
#include "ViewController.h"

using namespace bb::cascades;

ApplicationUI::ApplicationUI(bb::cascades::Application *app)
        : QObject(app) {
    // create scene document from main.qml asset
    // set parent to created document to ensure it exists for the whole application lifetime
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);

    // Initialize ViewModel and ViewController
    ViewModel* viewModel = new ViewModel();
    ViewController* viewController = new ViewController();

    qml->setContextProperty("_viewModel", viewModel);
    qml->setContextProperty("_viewController", viewController);

    // Update the underlying model for ViewModel and ViewController
    Model* model = new Model();
    viewModel->setModel(model);
    viewController->setModel(model);

    // create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();
    // set created root object as a scene
    app->setScene(root);
}


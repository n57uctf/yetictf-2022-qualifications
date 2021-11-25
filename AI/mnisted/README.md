__Category__: 
* AI

__Author__: 
* @dantetemplar

__Description__: 
We trained the model especially for you, but the deadline was jamming us in the corner - so we didn't have time to check ... BUT! Don't worry, we'll send you the test data ... P.S.: mean, std = [0.1307, 0.3081]

*model*: `torch.save(anal_model.state(dict),
“models/anal-model-jit-script.pth”)`

__Flag__:
* YetiCTF{i_hate_these_dataset_anomalies}

__Files__:
* files\MNIST_test_data.zip
* files\anal-model-jit-script.pth

__Hints__:
* just check the model... and see which pictures is wrong... That's how tests do, isn't it?;
* see metadata of these pictures;

__Writeup__:
* See dev\writeup.ipynb
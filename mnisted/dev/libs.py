import torch
import torchmetrics
import pandas as pd
import os
from tqdm.notebook import tqdm
from torch.utils import tensorboard
from PIL import Image
from collections import namedtuple

class DefaultDataset(torch.utils.data.Dataset):
    def __init__(self, images_dir, dataframe, names_column, labels_column, features_transform=None, labels_transform=None):
        self.images_dir = images_dir
        self.names_column = names_column
        self.labels_column = labels_column
        existing_image_names = self.files(images_dir)
        self.dataframe = dataframe[dataframe[self.names_column].isin(existing_image_names)] 
        self.image_names = self.dataframe[self.names_column]
        self.labels = self.dataframe[self.labels_column]
        
        self.features_transform = features_transform
        self.labels_transform = labels_transform
        
    @staticmethod
    def files(path):
        for file in os.listdir(path):
            if os.path.isfile(os.path.join(path, file)):
                yield file

    def __getitem__(self, index):
        image_name  = self.image_names.iloc[index]
        labels = self.labels.iloc[index]
        file_path = os.path.join(self.images_dir, image_name)
        os.path.exists(file_path)
        image = Image.open(file_path)
        features = self.features_transform(image) if self.features_transform else image
        labels = self.labels_transform(labels) if self.labels_transform else labels

        return (features, labels)
    
    def __len__(self):
        return len(self.image_names)
    

class DefaultLogger():
    def __init__():
        
        self.metrics = metrics
        self.targetmetric = targetmetric
        self.HistoryWrap = namedtuple("HistoryWrap", ["steps" ,"epochs"])
        self.history = dict()
        self.history_api = dict()

        self.logdir = logdir 
        self.checkpointpath = checkpointpath
        self._checkpointrule_ = lambda score, bestscore: score if any(bestscore == None, score >= bestscore)
        
        PbarsWrap = namedtuple("PbarsWrap", ["steps", "epochs"])
        self.__pbars__ = dict(steps=tuple(tqdm(desc="valid steps", unit="steps", leave=True), 
                                          tqdm(desc="train steps", unit="steps", leave=True)), 
                              epochs=tqdm(desc="Epochs", unit="epochs", leave=True))
        self.pbars_api = PbarsWrap(steps=self.__pbars__["steps"], epochs=self.__pbars__["epochs"])
    
    @property
    def metrics():
        return self.__metrics__    
    
    @metrics.setter
    def metrics(self, value):
        if isinstance(value, dict):
            value = (value["valid"], value["train"])
        elif isinstance(value, (list, tuple)):
            value = tuple(value)
        else:
            value = (value, value)
        
        for is_train, metric in enumerate(value):
            if metric:
                metric = torchmetrics.MetricCollection(metric)
            else:
                metric = []
        
        if not value[0] or not value[1]: 
            print(f"Attention! Unknown metric!")
                
        self.__metrics__ = value
    @property
    def targetmetric(self):
        return self.__targetmetric__
    
    @targetmetric.setter
    def targetmetric(self, value):
        if self.metrics[0]:
            if value not in self.metrics[0].keys():
                value = None
        else:
            value = None
        self.__targetmetric__ = value
        
    def init_model(model):
        if not hasattr(model, "name"):
            model.name = model.__class__.__name__
        self.model = model
        self.bestscore = None
        self._curepoch_ = 1
        self._curstep_ = [1, 1]
        
        self.pbars_api.epochs.reset(total=self.gym.num_of_epochs) 
        self.pbars.api.steps[0].reset(total=len(self.gym.dataloaders["valid"])) 
        self.pbars.api.steps[1].reset(total=len(self.gym.dataloaders["train"]))     
        
        metric.reset() for metric in self.metrics
        self.history.update(model.name = dict(steps=([],[]), epochs=([], [])))
        self.history_api.update(model.name = self.HistoryWrap(steps=self.history[self.model.name]["steps"], 
                                                              epochs=self.history[self.model.name]["epochs"]))    
        
        example_inputs = self.gym.dataloaders["train"].dataset[0][0]
        new_shape = (1,) + tuple(example_inputs.shape)
        self.__tensorboard__.add_graph(self.model, example_inputs.view(new_shape))  
                
    def init_gym(gym):
        if not hasattr(gym, "name"):
            gym.name = gym.__class__.__name__
        self.gym = gym
        self.__tensorboard__ = tensorboard.SummaryWriter(log_dir=self.logdir + "/tensorboard", comment=f"{self.gym.name}")
        self.bestscore = None
        print(self.gym.desc)
        
    def epoch():
        self.pbars_api.steps[0].reset()
        self.pbars_api.steps[1].reset()
        self._curepoch_ += 1
        self._curstep_ = [1, 1]
        self.pbars_api.epochs.update()   

    def loop(self, is_train):
        phase = "train" if is_train else "valid"

        metric = self.metrics[is_train]
        current_score = metric.compute()
        self.history_api[self.model.name].epochs(is_train).append(current_score)
        metric.reset()

        for metric_name, value in current_score.items():
             self._tensorboard_.add_scalars(f'{metric_name}/epochs/{phase}', {self.model.name: value}, self._curepoch_)

        if phase == "valid" and self.targetmetric:
            checkpoint = self._checkpointrule_(current_score[self.targetmetric], self.bestscore)
            if checkpoint:
                print(f"The validation score({self.target_metric_key}) has improved from {self.bestscore} to {checkpoint}... Saving model.")
                self.bestscore = checkpoint
                PATH = f"{self.checkpointpath}/{model.name}.pth"
                torch.save(self.model.state_dict(), PATH)
                    
    def step(self, is_train, logits, labels):
        phase = "train" if is_train else "valid"
        
        metric = self.metrics[is_train]
        _logits_, _labels_ = logits.to(), labels.detach().cpu()
        score = metric(_logits_, _labels_)
        self.history_api[self.model.name].steps[is_train].append(score)
        self.pbars_api.steps[is_train].update()

        for metric_name, value in current_score.items():
            self.__tensorboard__.add_scalars(f'{metric_name}/steps/{phase}', {self.model.name: value}, self._curstep_[is_train])
        self._curstep_[is_train] += 1      
    
class DefaultGym():
    def __init__(self, num_of_epochs, criterion, optimizer_wrap, scheduler_wrap, logger, name=None):
        
        self.num_of_epochs = num_of_epochs
                
        self.criterion = criterion
        self.optimizer_wrap = optimizer_wrap
        self.scheduler_wrap = scheduler_wrap
        
        self.device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
        
        self.logger = logger
        
        if name:
            self.name = name 
        else:
            self.name = self.__class__.__name__
            
    desc = property()
    @desc.getter
    def desc(self):
        if not self._desc_:
            self._desc_ = f"""\r
            ####################  The training room({self.name})  #####################################
             Options of gym:
                * criterion - {self.criterion.__class__};
                * optimizer - {self.optimizer.__dict__['defaults']};
                * scheduler - {self.scheduler.__dict__};

             Dataloaders: 
                * train - {len(self.dataloaders["train"])} batches | {len(self.dataloaders["train"].dataset)} images
                * valid - {len(self.dataloaders["valid"])} batches | {len(self.dataloaders["valid"].dataset)} images
            ################################################################################################"""
        return self._desc_
    
    def __str__(self):
        return self.desc
    
    def init_model(self, model, dataloaders):
        self.model = model
        self.dataloaders = dataloaders
        self.optimizer = self.optimizer_wrap(self.model)
        self.scheduler = self.scheduler_wrap(self.optimizer)
        
        if not hasattr(self.logger, "gym"):
            self.logger.init_gym(gym)
        self.logger.init_model(model)
        return self.model.to(self.device)
    
    def epoch(self, model, dataloaders):
        with torch.cuda.device(self.device):
            self.loop(model, dataloaders["train"], is_train=True)
            self.loop(model, dataloaders["valid"], is_train=False)
            self.scheduler.step()
        self.logger.epoch()
        
    def loop(self, model, dataloader, is_train: bool):
        with torch.set_grad_enabled(is_train):
            model.train() if is_train else model.eval()
            for features, labels in dataloader:
                features = features.to(self.device)
                labels = labels.to(self.device)
                self.step(model, features, labels, is_train)
            else:
                self.logger.loop(is_train)
                    
    def step(self, model, features, labels, is_train: bool):
        if is_train:
            logits = model(features)
            loss = self.criterion(logits, labels)
            self.optimizer.zero_grad()
            loss.backward()
            self.optimizer.step()
        else:
            logits = model(features)
        self.logger.step(is_train, logits, labels)
        
class DefaultTrainer():
    def __init__(self, dataloaders, gyms):
        self.gyms = gyms
        self.dataloaders = dataloaders
        
    def fit(self, model):
        self.era(model, self.dataloaders, self.gyms)
        return model
    
    def era(self, model, dataloaders, gyms):
        for gym in gyms:
            model = gym.init_model(model, dataloaders)
            self.period(model, dataloaders, gym)
    
    def period(self, model, dataloaders, gym):
        for epoch_id in range(gym.num_of_epochs):
            self.epoch(model, dataloaders, gym)
        
    def epoch(self, model, dataloaders, gym):
        gym.epoch(model, dataloaders)
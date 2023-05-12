#### mintimate 的 brew 安装脚本
```bash
/bin/zsh -c "$(curl -fsSL 'https://api.host.mintimate.cn/fileHost/public/download/TCD')"
```

#### 内置 [中科大镜像]，安装Homebrew
```bash
/bin/zsh -c "$(curl -fsSL https://gitee.com/cunkai/HomebrewCN/raw/master/Homebrew.sh)"
```

#### 卸载Homebrew 安装的软件及依赖
```bash
brew tap beeftornado/rmtree

brew rmtree git
brew cleanup
```

#### oh-my-zsh
```bash
zsh -c "$(curl -fsSL 'https://api.host.mintimate.cn/fileHost/public/download/1P0R')"
```

#### git config
```bash
git config --global user.name
git config --global user.email

git config --global init.defaultBranch master
```

#### ssh

生成ssh
```bash
ssh-keygen -t ed25519 -C "your_email@example.com"
```

测试ssh
```bash
ssh -T git@github.com. # Attempts to ssh to GitHub
```

多用户ssh配置
```
Host github.com
 HostName github.com
 User git
 IdentityFile ~/.ssh/id_iMac
```

#### JetBrains

实时模版

use:
```
const [$STATE$, $SET_STATE$] = useState<$STATE_TYPE$>($INITIAL_SATE$)
-   concat("set",capitalize(STATE))
-   "any"
```
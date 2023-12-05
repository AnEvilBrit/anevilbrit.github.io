class LatestCommitComponent extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      date: "",
    };
  }

  componentDidMount() {
    // Replace this with your own repo
    // https://api.github.com/repos/:owner/:repo/branches/master
    fetch(
      "https://api.github.com/repos/AnEvilBrit/anevilbrit.github.io/branches/master"
    )
      .then(response => {
        response.json().then(json => {
          console.log(json);
          this.setState({
            date: json.commit.commit.author.date,
          });
        });
      })
      .catch(error => {
        console.log(error);
      });
  }

  render() {
    return (
        <div>{this.state.date}</div>
    );
  }
}

ReactDOM.render(<LatestCommitComponent />, document.getElementById("root"));
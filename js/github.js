/**
 * See https://developer.github.com/v3/repos/branches/#get-branch
 *
 * Example Github api request:
 * https://api.github.com/repos/ta-dachi/eatsleepcode.tech/branches/master
 */
class LatestCommitComponent extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      date : "",
    };
  }
  
  componentDidMount() {
    // Replace this with your own repo
    // https://api.github.com/repos/:owner/:repo/branches/master
    fetch(
      "https://api.github.com/repos/AnEvilBrit/anevilbrit.github.io/branches/main"
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
      <div>
        Here you can view all the small projects and items I have created. (Updated as of <time class="timeago" datetime={this.state.date}>Time Not Loaded!</time>)
      </div>
    );
  }
}

ReactDOM.render(<LatestCommitComponent />, document.getElementById("time"));
open Survey;

[@react.component]
let make = () => {
  let (questions: array(Question.t), setQuestions) =
    React.useState(() => [||]);
  let (name, setName) = React.useState(() => "");

  let (desc, setDesc) = React.useState(() => "");

  let (create, createSurvey) = SurveyMutation.useCreate();

  <Layout>
    <SurveyForm
      name
      setName
      desc
      setDesc
      fetching={create.fetching}
      questions
      setQuestions
      request={() =>
        createSurvey(
          ~formInput={
            "title": name,
            "content": desc,
            "questions": SurveyForm.mapQuestions(questions),
          },
          (),
        )
      }
    />
  </Layout>;
};